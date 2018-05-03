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


std::string & ltrim(std::string & str)
{
    auto it2 =  std::find_if( str.begin() , str.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
    str.erase( str.begin() , it2);
    return str;
}

std::string & rtrim(std::string & str)
{
    auto it1 =  std::find_if( str.rbegin() , str.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
    str.erase( it1.base() , str.end() );
    return str;
}
//This function takes a std::string input and outputs a std::vector<std::string>
// with the question as the first element and the following elements as the options
// int flag = 0 for beat the q, 1 for HQ trivia

vector<string> ocr_screenshot(string screenshot_path){
    auto *api = new tesseract::TessBaseAPI();
    vector<string> *output = new vector<string>;

    if (api->Init(nullptr, "eng")) {
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
    int left_position = 0;
    int box_width = width;

    int top_position_question = 0;
    int box_height_question = 0;


    int top_position_option_1 = 0;
    int top_position_option_2 = 0;
    int top_position_option_3 = 0;
    int box_height_option = 0;


//Beat the Q things
////        left_position = (int) (((double) width) * 0.0735);
////        top_position = (int) (((double) height) * 0.1389);
////        box_width = (int) (((double) width) * 0.89869);
////        box_height = (int) (((double) height) * 0.64815);


    //HQ proportions
    left_position = (int) (((double) width) * 0.0533);
    box_width = (int) (((double) width) * 0.88);

    top_position_question = (int) (((double) height) * 0.18473);
    box_height_question = (int) (((double) height) * 0.20525);

    box_height_option = (int) (((double) height) * 0.05542);
    top_position_option_1 = (int) (((double) height) * 0.43103);
    top_position_option_2 = (int) (((double) height) * 0.49671);
    top_position_option_3 = (int) (((double) height) * 0.57266);



    //set the coordinates for where to look on the screenshot
    //question
    api->SetRectangle(left_position, top_position_question, box_width, box_height_question);
    // Get OCR result
    string text_question(api->GetUTF8Text());
    output->push_back(text_question);

//    cout << text_question << endl;

    //option 1
    api->SetRectangle(left_position, top_position_option_1, box_width, box_height_option);
    // Get OCR result
    string text_option_1(api->GetUTF8Text());
//    cout << text_option_1 << endl;
    output->push_back(text_option_1);

    api->SetRectangle(left_position, top_position_option_2, box_width, box_height_option);
    // Get OCR result
    string text_option_2(api->GetUTF8Text());
//    cout << text_option_2 << endl;
    output->push_back(text_option_2);

    api->SetRectangle(left_position, top_position_option_3, box_width, box_height_option);
    // Get OCR result
    string text_option_3(api->GetUTF8Text());
//    cout << text_option_3 << endl;
    output->push_back(text_option_3);


    for(auto &s : *output){
        ltrim(rtrim(s)); //remove whitespace
        replace( s.begin(), s.end(), '\n', ' '); // replace all '\n' to ' '
        std::transform(s.begin(), s.end(), s.begin(), ::tolower); //lowercase everything
//        cout << s << endl; //print it
    }



    // Destroy used object and release memory
    api->End();
//    delete [] outText;
    pixDestroy(&screenshot);

    return *output;
}







#endif //INC_4122_PROJECT_IMAGE_PROCESSING_H
