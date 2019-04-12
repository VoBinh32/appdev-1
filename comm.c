#include "comm.h"
#include "sound.h"
#include <curl/curl.h>
#include <math.h>
#include <stdio.h>
// This function will calcultae 1s of sound samples into 8-peices of
// slow decibel( ISO standard), this date is calculated as 125ms of samples
// the first haft of function is to calculate, the 2nd  haft is to perform
// libcurl communication

void sendDATA(short s[]) {
    double rms[8], db[8];
    int i, j;

    for (i = 0; i < 8; i++) {
        double sum = 0.0;
        for (j = 0; j < 2000; j++) {
            sum += s[i * 2000 + j] * s[i * 2000 + j];
        }
        rms[i] = sqrt(sum / 2000);
        db[i] = 20 * log10(rms[i]);
    }
    // using libcurl function to send data
    CURL *c;
    CURLcode res;
    char poststr[128];
    // post string should be in "db=num1;num2;...;num8" format
    sprintf(poststr, "db=%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f;%.2f", db[0], db[1],
            db[2], db[3], db[4], db[5], db[6], db[7]);
#ifdef DEBUG
    printf("postr = %s\n", poststr);
#endif
    curl_global_init(CURL_GLOBAL_ALL);
    c = curl_easy_init();
    if (c) {
        curl_easy_setopt(c, CURLOPT_URL, URL);
        curl_easy_setopt(c, CURLOPT_POSTFIELDS, poststr);
        res = curl_easy_perform(c);
        if (res != CURLE_OK)
            printf("Communication failed!\n");

        curl_easy_cleanup(c);
    }
    curl_global_cleanup();
}
