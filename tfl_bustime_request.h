#include <curl/curl.h>
#include <stdlib.h>
#include <stdio.h>


CURLcode request()
{
    CURL *curl = curl_easy_init();
    if (!curl) {
        return;
    }
    curl_easy_setopt(curl, CURLOPT_URL, "http://countdown.api.tfl.gov.uk/interfaces/ura/stream_V1");
    CURLcode result = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    return result;
}