#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//macro definitions: uncomment to log info related to specific module
// #define LOG_IMAGE_CONFIG  //to print data in image file header to stdout
// #define LOG_ENCODE  //to print encoded data, number of bytes encoded and fwrite function return value each time a bit is embedded in the pixel array
#define MAGIC_STRING "$#@"  //used to check if image is steged or not

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
int checkClaOption(int claArgumentCount, char *claArgumentArr[]);  //used to check whether encode or decode option is selected
void collectHeaderInfo(Image *image,char *pathOfFile);
void collectSecretFileInfo(Secret *secret, char *pathOfFile);
void checkImgCapacity(Secret *secret, Image *image); //used to check if image is big enough to store secret information
void initOutputFile(Output *output, char *pathOfFile);
void displayImageData(Image *image);
void embedMagicString(Image *image);
int encode(Secret *secret, Image *image);
int decodeMagicString(Image *image);
int decode(Image *image, Output *output);
void checkEncodeStatus(int bytesToBeDecoded, uchar modifiedByteValue, int bit, size_t numBytesWritten); //logs status after encode function is called
