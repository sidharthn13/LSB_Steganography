#include<stdio.h>
#include<stdlib.h>

//macro definitions: uncomment to log info related to specific module
// #define LOG_CONFIG  //to print data in image file header to stdout
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

//function prototypes:
void collectHeaderInfo(Image *image);
void collectSecretFileInfo(Secret *secret);
void displayImageData(Image *image);
int encode(Secret *secret, Image *image);
int decode(Image *image);
void checkEncodeStatus(int bytesToBeDecoded, uchar modifiedByteValue, int bit, size_t numBytesWritten); //logs status after encode function is called
