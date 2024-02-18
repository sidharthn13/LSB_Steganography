#include<stdio.h>
#include<stdlib.h>

// //macro definitions:
// #define LOG  //to print data in image file header to stdout 

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
