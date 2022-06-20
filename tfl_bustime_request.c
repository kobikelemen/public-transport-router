#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>


int main()
{
    
    CURL *curl = curl_easy_init();


    if (!curl) {
        return EXIT_FAILURE;
    }

    curl_easy_setopt(curl, CURLOPT_URL, "http://countdown.api.tfl.gov.uk/interfaces/ura/stream_V1");
    // curl_easy_setopt()

    CURLcode result = curl_easy_perform(curl);

    // if (result != CURL_OK) {
    //     printf(stderr, "shit");
    // }


    curl_easy_cleanup(curl);
}