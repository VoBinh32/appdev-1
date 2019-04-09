#include <stdio.h>
#include <math.h>
#include "sound.h"
#include "screen.h"

// this function takes 1 sec of sample (16000) and caculate
// 80 pieces of RMS value, and then turn these values
// into decibels, and display them as a barchart
void displayWAVDATA(short s[]){
	double rms[80]; // because of 16000 samples, 16000/80=200
					// therefore every 200 samples makes one RMS
	int i, j;
	short *ptr = s;		// we use a pointer, pointing to the beginning of array
	int db[80];
	
	for(i=0; i<80; i++){
		double sum = 0;		// accumulate sum of squares
		for(j=0; j<200; j++){
			sum += (*ptr) * (*ptr);
			ptr++;			// pointing to the next sample
		}
		rms[i] = sqrt(sum/200);
		db[i] = 20*log10(rms[i]);	// decibel value
#ifdef DEBUG
		printf("rms[%d] = %f\n", i, rms[i]);
#endif
	}
#ifndef DEBUG
	barChart(db);
#endif
}

void showID(char *name, char *value){
	printf("%s: ",name);
	for(int i=0; i<4; i++)
		printf("%c", value[i]);
	puts("");
}

//function definition
void displayWAVHDR(struct WAVHDR h){
#ifdef DEBUG
	showID("Chunk ID", h.ChunkID);
	printf("Chunk size: %d\n", h.ChunkSize);
	showID("Format", h.Format);
	showID("Subchunk 1 ID", h.Subchunk1ID);
	printf("Subchunk 1 size: %d\n", h.Subchunk1Size);
	printf("Audio format: %d\n", h.AudioFormat);
	printf("Number of channels: %d\n", h.NumChannels);
	printf("Sample rate: %d\n", h.SampleRate);
	printf("Byte rate: %d\n", h.ByteRate);
	printf("Block align: %d\n", h.BlockAlign);
	printf("Bits per samle: %d\n", h.BitsPerSample);
	showID("Subchunk 2 ID", h.Subchunk2ID);
	printf("Subchunk 2 size: %d\n", h.Subchunk2Size);
#else
	setColors(RED,bg(BLUE));
	printf("\033[1;1H");
	printf("test.wav            \n");
	setColors(YELLOW,bg(GREEN));
	printf("\033[1;21H");
	printf("Sample rate=%d      \n",h.SampleRate);
	setColors(WHITE,bg(MAGENTA));
	printf("\033[1;61H");
	printf("Duration=%.2f       \n",(float)h.Subchunk2Size/h.ByteRate);	
#endif
}