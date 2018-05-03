/*
 * Michael Brzozowski 4/28/18
 * Threaded 5/3/18
 */

#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <vector>
#include <string>
#include <thread>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}

void getResult(std::string* search, std::vector<std::string>* responses, int index) {
    auto curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, search->c_str());

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

        (*responses)[index] = response_string;
    }
}

std::vector<std::string> getResults(std::vector<std::string> &searches) {
    std::vector<std::thread*> responseThreads;
    std::vector<std::string> responses(searches.size());
    for (int i = 0; i < searches.size(); i++) {
        responseThreads.push_back(new std::thread{getResult, &searches[i], &responses, i});
    }
    for (auto &t : responseThreads) {
        t->join();
    }
    for (int i = 0; i < searches.size(); i++) {
        getResult(&searches[i], &responses, i);
        std::cout << "response i: " << i << "\n" << responses[i] << std::endl;
    }
    return responses;
}


//Insert parameters into the search url
std::string createGoogleSearch(std::string term, int numResults) {
    std::stringstream ss;
    ss << "https://www.googleapis.com/customsearch/v1?q=" << term << "&num=" << numResults
       << "&start=1&key=AIzaSyCHAQ5Df-PcBzhiSYLJlvRoCc-qXK1WrD4&cx=013405187926511280840:o0p-h54b9ze";
    return ss.str();
}

