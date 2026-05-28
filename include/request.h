//
// Created by rhysh on 28/05/2026.
//

#ifndef HTTPHEALTHD_HEALTH_CHECK_H
#define HTTPHEALTHD_HEALTH_CHECK_H

typedef struct {
    long response_code;
} response_data;

response_data ping(char *URL);

int is_response_ok(long response_code);

#endif //HTTPHEALTHD_HEALTH_CHECK_H
