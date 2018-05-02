#include <iostream>
#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>
#include <fstream>
#include <cstring>
#include <bits/stdc++.h>
#include "image_processing.h"
#include "extracter.h"
#include "json/json.h"
#include "search.h"
#include "question_format.h"
#include <vector>

//Need install these on linux
//sudo apt install libjsoncpp-dev
//sudo apt install tesseract-ocr
//sudo apt install libtesseract-dev
//sudo apt install libleptonica-dev
//sudo apt install libcurl4-openssl-dev



using namespace std;
int main() {

    //returns vector of strings, first string being the question, the following being the options
    vector<string> questions_answers = ocr_screenshot("../test_data/test1.png");
    
    //loop for testing ocr with test data
//    for(int i = 0; i < questions_answers.size(); i++) {
//        cout << questions_answers[i] << endl;
//    }
      
      // formatting question for search

//    std::string question = questions_answers[0];
//    formatString(question);
//    std::vector<std::string> dictionary = {"a", "the", "that", "these", "is", "what", "called", "which", "of"};
//    reduceString(question, dictionary);
//    cout << question << endl;

    // searching
    std::vector<std::string> searches;
    searches.emplace_back(createGoogleSearch(questions_answers[0], 4));                      // just question
    searches.emplace_back(createGoogleSearch(questions_answers[0]+ " " + questions_answers[1], 4)); // question + choice 1
    searches.emplace_back(createGoogleSearch(questions_answers[0]+ " " + questions_answers[2], 4)); // question + choice 2
    searches.emplace_back(createGoogleSearch(questions_answers[0]+ " " + questions_answers[3], 4)); // question + choice 3

    // perform search
    std::vector<std::string> outputs = getResults(searches);

    for(int i = 0; i < outputs.size(); i++) {
         cout << outputs[i] << endl;
    }

    // extract string from search result
    std::vector<std::string> results;
    for (int i = 0; i <= searches.size(); i++)
    {
        results.emplace_back(getString(outputs[i]));
    }


    // extract number of results from search result
    std::vector<std::string> numResults;
    for (int i = 0; i <= searches.size(); i++)
    {
        numResults.emplace_back(getNumResults(outputs[i]));
    }

    //method 1//
    string answer1;
    int max = 0;
    for(int i = 1; i <= questions_answers.size(); i++)
    {
        stringstream ss(results[0]);
        int cnt=0;
        while(ss >> results[0])
        {
            if(results[0] == questions_answers[i])
                cnt++;
        }
        if (cnt > max)
        {
            max = cnt;
            answer1 = questions_answers[i];
        }
    }

    //method2//
    int maxNumResults = 0;
    string answer2;
    for (int i = 1; i <= numResults.size(); i++)
    {
        if(std::stoi(numResults[i]) > maxNumResults)
        {
            maxNumResults = std::stoi(numResults[i]);
        }
    }

    //show two answers
    cout << answer1 << endl;
    cout << answer2 << endl;

}
