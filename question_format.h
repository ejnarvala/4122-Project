/* William Trimmer 4/30/18
 * Functions to format OCR results for searching
*/
// Remove unnecessary words from question



#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>

 void removeWords(string &formattedString, string word) {
    size_t foundWord = formattedString.find(word);
    if(string::npos != foundWord) {
        if(foundWord == 0) {
            formattedString.erase(foundWord, word.size()+1);
        }
        else {
            formattedString.erase(foundWord-1, word.size()+1);
        }
    }
}
// tried to add loop with dictionary to remove words, but too many errors
// remove spaces and question mark from string
void formatString(string &string) {
    for(int i = 0; i < string.size(); i++) {
        if((string[i] == ' ') || (string[i] == '?') || (string[i] == '-')) {
            string[i] = '+';
        }
        string.erase(remove(string.begin(), string.end(), '"'), string.end());
        string.erase(remove(string.begin(), string.end(), ','), string.end());
    }
}

// function that takes vector with desired words and removes from string
void reduceString(string &formattedString, vector<std::string> dict) {
    for(int i = 0; i < dict.size(); i++) {
        string word = dict[i];
        removeWords(formattedString, word);
        cout << formattedString << endl;
    }
}

void convertOne(string string1, vector<string>& vector1) {
     size_t i, j;
     string answer1, answer2, answer3, string2;
     vector<string> answers;

     i = string1.find("?");
     j = string1.find_last_of(' ');
     answer1 = string1.substr(j+1, string1.length() - j);
     string2 = string1.substr(0, j);

     j = string2.find_last_of(' ');
     answer2 = string2.substr(i+2, j -(i+2));
     answer3 = string2.substr(j+1, string2.length()-j);
     string1.erase(i+1, string1.length());
     vector1.clear();
     vector1.push_back(string1);
     vector1.push_back(answer1);
     vector1.push_back(answer2);
     vector1.push_back(answer3);
 }

void convertTwo(string string1, vector<string>& vector1) {
    //find question mark
    size_t i, j;
    string answer1, answer2;
    vector<string> answers;

    i = string1.find('?');
    // increment i by two
    j = string1.find_last_of(' ');
    answer1 = string1.substr(i+2, j-(i+2));
    answer2 = string1.substr(j+1, string1.length()-j);
    string1.erase(i+1, string1.length());
    vector1[0] = string1;
    vector1[2] = answer1;
    vector1[3] = answer2;
}
