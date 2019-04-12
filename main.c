#include "comm.h"
#include "screen.h"
#include "sound.h"
#include <signal.h> // for random numbers
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for randomization (using system time)

int main(int argc, char **argv) {
    if (argc == 2) {
        int ch;
        printf("How many channels (1:mono, 2:stereo)");
        scanf("%d", &ch);
        float duration;
        printf("How long is the test tone?(1-10s):");
        scanf("%f", &duration);
        testTone(ch, atoi(argv[1]), duration);
        return 0;
    }

    FILE *f;
    short sd[RATE]; // for all sample in 1 sec
    while (1) {
        int ret = system(CMD);
        if (ret == SIGINT)
            break; // break signal by keyboard

        f = fopen("test.wav", "r");
        if (f == NULL) {
            printf("Cannot open the wav file.\n");
            return 1;
        }

        clearScreen();
        setColors(CYAN, bg(BLACK));

        struct WAVHDR h;              // instance of wave header
        fread(&h, sizeof(h), 1, f);   // read wav header to h
        fread(&sd, sizeof(sd), 1, f); // read WAV data
        fclose(f);
        displayWAVHDR(h);   // show wav header information
        displayWAVDATA(sd); // show data wave data information
        sendDATA(sd);
    }

    resetColors();
}