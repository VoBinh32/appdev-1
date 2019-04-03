//this is main.c
#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <time.h>
#include "screen.h"
#include "sound.h"

int main(){
	FILE *f;
	short sd[RATE]; // for all sample in 1 sec
	while(1){
		int ret = system(CMD);
		if(ret == SIGINT) break; // break signal by keyboard
		
		f = fopen("test.wav", "r");
		clearScreen();
		setColors(CYAN, bg(BLACK));

		if(f == NULL){
			printf("cannot open the wav file.\n");
			return 1;
		}
		
		struct WAVHDR h;	// instance of wave header
		fread(&h, sizeof(h), 1, f);		// read wav header to h
		fread(&sd, sizeof(sd), 1, f);	// read WAV data
		fclose(f);
		displayWAVHDR(h);	// show wav header information
		displayWAVDATA(sd);	// show data wave data information		
	}
	
	resetColors();
}