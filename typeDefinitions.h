#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//macro definitions: uncomment to log info related to specific module
// #define LOG_IMAGE_CONFIG  //to print data in image file header to stdout
// #define LOG_ENCODE  //to print encoded data, number of bytes encoded and fwrite function return value each time a bit is embedded in the pixel array

//data type definitions:
typedef unsigned int uint;
typedef unsigned short int usint;
typedef unsigned char uchar;

//structure definitions: 
typedef struct Image{
    char fileType[3];
    uint pixelArrayOffset;
    FILE *fileStream;
    usint bitsPerPixel;
    uint width;
    usint padding;
    uint pixelArraySize;
}Image;
typedef struct Secret{
    uint size;
    FILE *fileStream;
}Secret;
typedef struct Output{
    FILE *fileStream;
}Output;

//function prototypes:
int checkClaOption(int claArgumentCount, char *claArgumentArr[]);
void collectHeaderInfo(Image *image);
void collectSecretFileInfo(Secret *secret);
void initOutputFile(Output *output);
void displayImageData(Image *image);
int encode(Secret *secret, Image *image);
int decode(Image *image, Output *output);
void checkEncodeStatus(int bytesToBeDecoded, uchar modifiedByteValue, int bit, size_t numBytesWritten); //logs status after encode function is called
