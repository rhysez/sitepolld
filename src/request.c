#include "request.h"
#include <curl/curl.h>
#include <stdio.h>

int is_request_ok(long response_code) {
    return response_code >= 200 && response_code <= 299;
}

response_data ping(char *URL) {
    response_data rd;

    CURL *curl = curl_easy_init();
    if (!curl) {
        rd.response_code = 0;
        return rd;
    }

    CURLcode res = CURLE_OK;

    curl_easy_setopt(curl, CURLOPT_URL, URL);

    res = curl_easy_perform(curl);

    // If curl didn't fail
    if (res == CURLE_OK) {
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &rd.response_code);

        if (is_request_ok(rd.response_code)) {
            printf("[PING] Success: HTTP OK\n");
        } else {
            printf("[PING] HTTP error: %ld\n", rd.response_code);
        }
    } else {
        rd.response_code = 0;

        printf("[PING] curl failed: %s\n", curl_easy_strerror(res));
    }

    curl_easy_cleanup(curl);

    return rd;
}