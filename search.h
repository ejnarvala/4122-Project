/*
 * Michael Brzozowski 4/28/18
 *
 * download >
 * https://curl.haxx.se/download.html
 *
 * unzip, run these
 * ./configure
 * make
 * make install
 *
 */

#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <vector>
#include <string>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

std::vector<std::string> getResults(std::vector<std::string> &searches) {
    std::vector<std::string> responses;
    for (std::string search : searches) {
        auto curl = curl_easy_init();
        if (curl) {
            curl_easy_setopt(curl, CURLOPT_URL, search.c_str());

            //setup and execution of curl
            std::string response_string;
            std::string header_string;
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
            curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

            char *url;
            long response_code;
            double elapsed;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
            curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

            curl_easy_perform(curl);
            curl_easy_cleanup(curl);
            curl = nullptr;
            //
            responses.emplace_back(response_string);
        }
    }
    return responses;
}

/*
 * Insert parameters into the search url
 */

std::string createGoogleSearch(std::string term, int numResults) {
    std::stringstream ss;
    ss << "https://www.googleapis.com/customsearch/v1?q=" << term << "&num=" << numResults
       << "&start=1&key=AIzaSyCHAQ5Df-PcBzhiSYLJlvRoCc-qXK1WrD4&cx=013405187926511280840:o0p-h54b9ze";
    return ss.str();
}

/* William Trimmer 4/30/18
 * Functions to format OCR results for searching
*/
// Remove unnecessary words from question
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
