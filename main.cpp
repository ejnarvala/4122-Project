#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fstream>
#include <cstring>
#include "image_processing.h"
#include "extracter.h"

//Need install these on linux
//sudo apt install libjsoncpp-dev
//sudo apt install tesseract-ocr
//sudo apt install libtesseract-dev
//sudo apt install libleptonica-dev



int main() {

    //This is for testing jsonparser
    string extractedString;
    Json::Value root;
    Json::Reader reader;

    std::ifstream file("../searchResult.JSON");
    file >> root;


    extractedString = getString(root);
    cout << extractedString;

    //testFunction();
    return 0;
}
