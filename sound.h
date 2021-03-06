//  Constants definition
//#define DEBUG
#define PI 3.1415926
#define DUR 1
#define RATE 16000 // samples per second
#define CMD "arecord -r16000 -c1 -f S16_LE -d1 -q test.wav"

// data structures
struct WAVHDR {
    char ChunkID[4]; // it is "RIFF"
    int ChunkSize;   // 4 bytes num
    char Format[4];  // it is "WAVE"

    char Subchunk1ID[4]; //"fmt"
    int Subchunk1Size;   // PCM = 16
    short AudioFormat;   // shoud be "1"
    short NumChanels;    // Should be 1
    int SampleRate;      // 16000
    int ByteRate;        // 16000*NumChannels*BitsPerSample/8
    short BlockAlign;    // NumChannels*BitsPerSample
    short BitsSample;    // in our app, 16 (-f S16_LE)

    char Subchunk2ID[4]; //"data"
    int Subchunk2Size;   //
};

// function declarations
void displayWAVHDR(struct WAVHDR h);
void displayWAVDATA(short[]);
void testTone(int, int, float);
