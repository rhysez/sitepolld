#include "response.h"
#include <curl/curl.h>
#include <stdio.h>

int is_response_ok(long response_code) {
    return response_code >= 200 && response_code <= 299;
}

void on_response_ok(CURL *curl, response_data rd) {
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &rd.response_code);
    if (is_response_ok(rd.response_code)) {
        printf("[PING] Success: HTTP OK\n");
    } else {
        printf("[PING] HTTP error: %ld\n", rd.response_code);
    }
}

void on_response_not_ok(const CURLcode res, response_data *rd) {
    rd->response_code = 0;
    printf("[PING] curl failed: %s\n", curl_easy_strerror(res));
}

response_data ping(char *URL) {
    response_data rd = {};

    CURL *curl = curl_easy_init();
    if (!curl) {
        rd.response_code = 0;
        return rd;
    }

    curl_easy_setopt(curl, CURLOPT_URL, URL);
    const CURLcode res = curl_easy_perform(curl);

    // If curl didn't fail
    if (res == CURLE_OK) {
        on_response_ok(curl, rd);
    } else {
        on_response_not_ok(res, &rd);
    }

    curl_easy_cleanup(curl);

    return rd;
}