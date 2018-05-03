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
    vector<string> questions_answers = ocr_screenshot("../test_data/test3.png");
    
    //loop for testing ocr with test data
    if(questions_answers.size()){
        cout << "Question: " << questions_answers[0] << endl;
        for(int n = 1; n < questions_answers.size(); n++){
            cout << n << ". " << questions_answers[n] << endl;
        }
    }

    cout << endl;

// example
//    vector<string> questions_answers;
//    questions_answers.emplace_back("A single piece of clothing that covers the entire body is called what?");
//    questions_answers.emplace_back("whatsie");
//    questions_answers.emplace_back("whosie");
//    questions_answers.emplace_back("onesie");



      // formatting question for search

    std::string question = questions_answers[0];
    formatString(question);
    reduceString(question);
    formatString(questions_answers[1]);
    formatString(questions_answers[2]);
    formatString(questions_answers[3]);

    // searching
    std::vector<std::string> searches;
    searches.emplace_back(createGoogleSearch(question, 10));                      // just question
    searches.emplace_back(createGoogleSearch(question+questions_answers[1], 10)); // question + choice 1
    searches.emplace_back(createGoogleSearch(question+questions_answers[2], 10)); // question + choice 2
    searches.emplace_back(createGoogleSearch(question+questions_answers[3], 10)); // question + choice 3

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
    if(results[0].length() == 0){
        cout << "Ending program: no search results" << endl;
    }


    //method 1//
    string answer1;
    int method_1_answer_num;
    int max = 0;
    int counts[3];
    //cout << results[0];
    for(int i = 1; i < questions_answers.size(); i++)
    {
        //stringstream ss(results[0]);
        int cnt = 0;
        size_t nPos = results[0].find(questions_answers[i],0);
        while(nPos != string::npos)
        {
//            if(results[0] == questions_answers[i]){
//                cnt++;
//            }
            cnt++;
            nPos = results[0].find(questions_answers[i], nPos + 1);

        }
        if (cnt > max)
        {
            max = cnt;
            answer1 = questions_answers[i];
            method_1_answer_num = i;
        }
        counts[i-1] = cnt;
    }
    int sum = counts[0] + counts[1] + counts[2];
    double pct_hits[3];

    for (int j = 0; j < 3; ++j) {
        pct_hits[j] = (double)counts[j] / (double)sum;
        pct_hits[j] *= 100;
    }


    //method2//
    int maxNumResults = 0;
    string answer2;
    int counts2[3];
    int method_2_answer_num;
    for (int i = 1; i < numResults.size(); i++)
    {
        if(std::stoi(numResults[i]) > maxNumResults)
        {
            maxNumResults = std::stoi(numResults[i]);
            method_2_answer_num = i;
            answer2 = questions_answers[i];
        }
        counts2[i-1] = std::stoi(numResults[i]);
    }
    int sum2 = counts2[0] + counts2[1] + counts2[2];
    double pct_hits2[3];

    for (int j = 0; j < 3; ++j) {
        pct_hits2[j] = (double)counts2[j] / (double)sum2;
        pct_hits2[j] *= 100;

    }
//    cout << sum2 << " " << sum << endl;
//    cout << counts2[0] << " " << counts2[1] << " " <<  counts2[2] << endl;
//    cout << counts[0] << " " << counts[1] << " " <<  counts[2] << endl;
//    cout << pct_hits[0] << " " << pct_hits[1] << " " <<  pct_hits[2] << endl;
//    cout << pct_hits2[0] << " " << pct_hits2[1] << " " <<  pct_hits2[2] << endl;


    //show two answers
    //cout << counts[1];
    //cout << counts[2];
    if (counts[0] == 0 && counts[1] == 0 && counts[2] == 0) {
    cout << "Method 1 yielded no search hits" <<endl;
    }else{
        cout << "Method 1 Suggests: " << method_1_answer_num << ". " << answer1 << endl
             << "Hit Percentages: " << endl
             << pct_hits[0] << "%  " << pct_hits[1] << "%  " << pct_hits[2] << "%" << endl << endl;
    }
    cout << "Method 2 Suggests: " << method_2_answer_num << ". " << answer2 << endl
         << "Hit Percentages: " << endl << setprecision(2)
         << pct_hits2[0] <<"%  " << setprecision(2) << pct_hits2[1] << "%  " << setprecision(2) << pct_hits2[2] <<"%" << endl;


}
