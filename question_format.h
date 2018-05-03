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
