#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fstream>
#include <cstring>
#include "image_processing.h"
#include "extracter.h"





int main() {

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
