#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fstream>
#include <cstring>
#include "image_processing.h"
#include "extracter.h"
#include "json/json.h"
#include "search.h"
#include <vector>

//Need install these on linux
//sudo apt install libjsoncpp-dev
//sudo apt install tesseract-ocr
//sudo apt install libtesseract-dev
//sudo apt install libleptonica-dev
//sudo apt install libcurl4-openssl-dev



using namespace std;
int main() {

      string extractedString;
      string numResults;

    //returns vector of strings, first string being the question, the following being the options
//    vector<string> questions_answers = ocr_screenshot("../test_data/test1.png");
    
    //loop for testing ocr with test data
//    for(int i = 0; i < questions_answers.size(); i++) {
//        cout << questions_answers[i] << endl;
//    }

    // searching
    std::vector<std::string> searches;
    searches.emplace_back(createGoogleSearch("test", 4));
    searches.emplace_back(createGoogleSearch("computer", 2));

    // perform search
    std::vector<std::string> outputs = getResults(searches);

    // extract string from search result
    extractedString = getString(outputs[0]);
    cout << extractedString << "\n";

    // extract number of results from search result
    numResults = getNumResults(outputs[0]);
    cout << numResults << "\n";
}
