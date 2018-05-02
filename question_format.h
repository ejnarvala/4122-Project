
 /* William Trimmer 4/30/18
 * Functions to format OCR results for searching
*/
// Remove unnecessary words from question



#include <cstdio>
#include <iostream>
#include <cstring>
#include <vector>

 void removeWords(std::string &formattedString, std::string word) {
    std::size_t foundWord = formattedString.find(word);
    if(std::string::npos != foundWord) {
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
void formatString(std::string &string) {
    for(int i = 0; i < string.size(); i++) {
        if((string[i] == ' ') || (string[i] == '?')) {
            string[i] = '+';
        }
    }
}

// function that takes vector with desired words and removes from string
void reduceString(std::string &formattedString, std::vector<std::string> dict) {
    for(int i = 0; i < dict.size(); ++i) {
        std::string word = dict[i];
        removeWords(formattedString, word);
    }
}
