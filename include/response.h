//
// Created by rhysh on 28/05/2026.
//

#ifndef HTTPHEALTHD_HEALTH_CHECK_H
#define HTTPHEALTHD_HEALTH_CHECK_H
#include <curl/curl.h>

typedef struct {
    long response_code;
} response_data;

response_data ping(char *URL);

int is_response_ok(long response_code);

void on_response_ok(CURL *curl, response_data rd);
void on_response_not_ok(CURLcode res, response_data *rd);

#endif //HTTPHEALTHD_HEALTH_CHECK_H
