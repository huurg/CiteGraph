#ifndef EXAMPLES_HEADER

#include <iostream>
using namespace std;

#include <cstdlib>

// CURL
#include <curl/curl.h>

//rapidjson
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;

// EXAMPLE 1: Get an URL for journal article (using SSL) and place file contents into a char*. Then parse the output into JSON object (using rapidjson), find references for the article and output them as a list.

size_t write_callback(char* ptr, size_t ptr_size, size_t nmemb, void* userdata) {
    /*for(size_t i = 0; i < nmemb; i++) {
        cout << ptr[i];
    }
    cout << endl;*/
    SizeType refno = 3;

    Document ptr_d;
    ptr_d.Parse(ptr);
    assert(ptr_d.IsObject());
    assert(ptr_d.HasMember("message"));
    Value& my_message = ptr_d["message"];
    assert(my_message.HasMember("reference"));
    Value& my_reference = my_message["reference"];
    assert(my_reference.IsArray());
    cout << "Number of references: " << my_reference.Size() << endl;
    char DOI_string[1000];
    char DOI_command[1000];
    for(SizeType i = 0; i < my_reference.Size(); i++) {
        Value& this_reference = my_reference[i];
        assert(this_reference.IsObject());
        if(this_reference.HasMember("DOI")) {
            Value& this_DOI = this_reference["DOI"];
            assert(this_DOI.IsString());
            strcpy(DOI_string,this_DOI.GetString());
            sprintf(DOI_command, "start https://doi.org/%s", DOI_string);
            /*StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            this_DOI.Accept(writer);*/
            cout << DOI_string << endl;
            if(i==refno) {
                system(DOI_command);
            }
        }
    }

    return (ptr_size*nmemb);
}

void example_getanURLputinchararray() {
    CURL* curl = curl_easy_init();
    if(curl) {
        CURLcode res;
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.crossref.org/works/10.1103/PhysRevA.95.022316");
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        res = curl_easy_perform(curl);
        if(res) {
            cout << "Error code: " << res << endl;
        }
        curl_easy_cleanup(curl);
    }
}


// END EXAMPLE 1

#endif // EXAMPLES_HEADER
