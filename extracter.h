#include <cstdio>
#include <iostream>
#include <cstring>

// This is the JSON header
#include "jsoncpp/json/json.h"
#include "json/json.h"

using namespace std;

string getString(string searchResult)
{
 string result;// final extracted string

 Json::Value root;// this will store searchresult as json object
 Json::Reader reader; // json reader
 bool parsedSuccess = reader.parse(searchResult, root, false);

 if(not parsedSuccess)
 {
   cout<<"Failed to parse JSON"<<endl
       <<reader.getFormatedErrorMessages()
       <<endl;

 }
 const Json::Value items = root["items"];

 for(unsigned int index=0; index < items.size();++index)
 {
   result = result + items[index]["title"].asString();
   result = result + items[index]["snippet"].asString();
 }
 return result;
}



string getString(Json::Value root)
{
    string result;// final extracted string

    // Let's extract the items contained
    // in the root object
    const Json::Value items = root["items"];

    // Iterate over sequence elements to find title and snippet
    // concatenate onto the final extracted string
    for(unsigned int index=0; index < items.size();++index)
    {
        result = result + " " + items[index]["title"].asString();
        result = result + " " + items[index]["snippet"].asString();
    }
    return result;
}


string getNumResults(Json::Value root)
{
    string numResults;// final string

    // extract items in root object "queries"
    const Json::Value items = root["queries"]["request"];
    
    // extract total results
    numResults = items[0]["totalResults"].asString();
    return numResults;
}


string getNumResults(string searchResult)
{
    Json::Value root;// this will store searchresult as json object
    Json::Reader reader; // json reader
    bool parsedSuccess = reader.parse(searchResult, root, false);

    if(not parsedSuccess)
    {
        cout<<"Failed to parse JSON"<<endl
            <<reader.getFormatedErrorMessages()
            <<endl;

    }
    string numResults;// final string

    // extract items in root object "queries"
    const Json::Value items = root["queries"]["request"];

    // extract total results
    numResults = items[0]["totalResults"].asString();
    return numResults;
}
