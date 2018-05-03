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

bool invalidChar(char c) {
     return !(c>=0 && c <128);
 }
// tried to add loop with dictionary to remove words, but too many errors
// remove spaces and question mark from string
void formatString(string &string) {
    for(int i = 0; i < string.size(); i++) {
        if((string[i] == ' ') || (string[i] == '?') || (string[i] == '-')) {
            string[i] = '+';
        }
        if(string[i] == '"') {
            string.erase(remove(string.begin(), string.end(), '"'), string.end());
        }
        string.erase(remove(string.begin(), string.end(), ','), string.end());
    }
    string.erase(remove_if(string.begin(), string.end(), invalidChar),string.end());
}

// function that takes vector with desired words and removes from string
void reduceString(string &formattedString) {
    removeWords(formattedString, "what");
}
