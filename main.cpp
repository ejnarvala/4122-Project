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
    for(int i = 0; i < questions_answers.size(); i++) {
        cout << questions_answers[i] << endl;
    }

// example
//    vector<string> questions_answers;
//    questions_answers.emplace_back("A single piece of clothing that covers the entire body is called what?");
//    questions_answers.emplace_back("whatsie");
//    questions_answers.emplace_back("whosie");
//    questions_answers.emplace_back("onesie");



      // formatting question for search

    std::string question = questions_answers[0];
    formatString(question);
    std::vector<std::string> dictionary = {"a", "the", "that", "these", "is", "what", "called", "which", "of"};
    reduceString(question, dictionary);
    cout << question << endl;



    // searching
    std::vector<std::string> searches;
    searches.emplace_back(createGoogleSearch(question, 4));                      // just question
    searches.emplace_back(createGoogleSearch(question+questions_answers[1], 4)); // question + choice 1
    searches.emplace_back(createGoogleSearch(question+questions_answers[2], 4)); // question + choice 2
    searches.emplace_back(createGoogleSearch(question+questions_answers[3], 4)); // question + choice 3

    // perform search
    std::vector<std::string> outputs = getResults(searches);

    //for testing search
//    for(int i = 0; i < outputs.size(); i++) {
//         cout << outputs[i] << endl;
//    }


    // extract string from search result
    std::vector<std::string> results;
    for (int i = 0; i < searches.size(); i++)
    {
        results.emplace_back(getString(outputs[i]));
    }


    // extract number of results from search result
    std::vector<std::string> numResults;
    for (int i = 0; i < searches.size(); i++)
    {
        numResults.emplace_back(getNumResults(outputs[i]));
    }

    //method 1//
    string answer1;
    int max = 0;
    int counts[3];
    //cout << results[0];
    for(int i = 1; i < questions_answers.size(); i++)
    {
        stringstream ss(results[0]);
        int cnt = 0;
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
        counts[i-1] = cnt;
    }
    int sum = counts[0] + counts[1] + counts[2];
    double pct_hits[3];

    for (int j = 0; j < 3; ++j) {
        pct_hits[j] = (double)counts[j] / (double)sum;
    }


    //method2//
    int maxNumResults = 0;
    string answer2;
    int counts2[3];
    for (int i = 1; i < numResults.size(); i++)
    {
        if(std::stoi(numResults[i]) > maxNumResults)
        {
            maxNumResults = std::stoi(numResults[i]);
            answer2 = questions_answers[i];
        }
        counts2[i-1] = std::stoi(numResults[i]);
    }
    int sum2 = counts[0] + counts[1] + counts[2];
    double pct_hits2[3];

    for (int j = 0; j < 3; ++j) {
        pct_hits2[j] = (double)counts2[j] / (double)sum2;
    }

    //show two answers
    //cout << counts[1];
    //cout << counts[2];
    cout << "The question/answer search method yields " <<answer1 //<< " with the following hit% of the three answers: " << pct_hits[0] <<"  " << pct_hits[1] << "  " << pct_hits[2]
    << endl;
    cout << "The total hits method yields " <<answer2 //<<" with the following hit% of the three answers: " << pct_hits2[0] <<"  " << pct_hits2[1] << "  " << pct_hits2[2]
    << endl;

}
