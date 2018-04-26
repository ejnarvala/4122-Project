#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fstream>
#include <cstring>
#include "image_processing.h"
#include "extracter.h"
#include "json/json.h"
#include <vector>

//Need install these on linux
//sudo apt install libjsoncpp-dev
//sudo apt install tesseract-ocr
//sudo apt install libtesseract-dev
//sudo apt install libleptonica-dev


using namespace std;
int main() {

    //This is for testing jsonparser
//    string extractedString;
//    Json::Value root;
//    Json::Reader reader;
//
//    ifstream file("../searchResult.JSON");
//    file >> root;
//
//
//    extractedString = getString(root);
//    cout << extractedString;

    //returns vector of strings, first string being the question, the following being the options
//    vector<string> questions_answers = ocr_screenshot("../test_data/test1.png");
    
    //loop for testing ocr with test data
//    for(int i = 0; i < questions_answers.size(); i++) {
//        cout << questions_answers[i] << endl;
//    }

    return 0;
}
