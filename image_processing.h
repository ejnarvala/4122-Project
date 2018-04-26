//
// Created by Ejnar on 4/22/2018.
//

#ifndef INC_4122_PROJECT_IMAGE_PROCESSING_H
#define INC_4122_PROJECT_IMAGE_PROCESSING_H

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <vector>
#include <algorithm>



using namespace std;




//This function takes a std::string input and outputs a std::vector<std::string>
// with the question as the first element and the following elements as the options

vector<string> ocr_screenshot(string screenshot_path){
    tesseract::TessBaseAPI *api = new tesseract::TessBaseAPI();
    vector<string> *output = new vector<string>;

    if (api->Init(NULL, "eng")) {
        cout << "Could not initialize tesseract." << endl;
        return *output;
    }

    // Open input image with leptonica library
    Pix *screenshot = pixRead(screenshot_path.c_str());
    int width = pixGetWidth(screenshot);
    int height = pixGetHeight(screenshot);


    //set the image to the screenshot
    api->SetImage(screenshot);

    //compute the values based on percentages of where the question will appear
    auto left_position = (int) (((double) width) * 0.0735);
    auto top_position = (int) (((double) height) * 0.1389);
    auto box_width = (int) (((double) width) * 0.89869);
    auto box_height = (int) (((double) height) * 0.64815);

    //set the coordinates for where to look on the screenshot
    api->SetRectangle(left_position, top_position, box_width, box_height);

    // Get OCR result
    string outText(api->GetUTF8Text());
//    printf("OCR output:\n%s", outText);
//    cout << outText << endl;

    //lowercase the text
    std::transform(outText.begin(), outText.end(), outText.begin(), ::tolower);



    int question_end = outText.find("\n\n");
    int question_start = 0;


    int period_pos = outText.find(".");
    if (period_pos < 4){
        question_start = period_pos + 1;
    }

    string question = outText.substr(question_start, question_end);
    replace( question.begin(), question.end(), '\n', ' '); // replace all '\n' to ' '
    output->push_back(question);
    outText = outText.substr(question_end+2); // remove question from text

    int pos = outText.find("\n");
    int i = 0;
    while(pos != string::npos){
        output->push_back(outText.substr(i, pos-i));
        i = ++pos;
        pos = outText.find("\n", pos);
        if (pos == string::npos){
            output->push_back(outText.substr(i));
        }
    }
    // Destroy used object and release memory
    api->End();
//    delete [] outText;
    pixDestroy(&screenshot);

    return *output;
}







#endif //INC_4122_PROJECT_IMAGE_PROCESSING_H
