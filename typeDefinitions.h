#include<stdio.h>
#include<stdlib.h>

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
    uint size;
}Image;

typedef struct Secret{
    uint size;
    FILE *fileStream;
}Secret;

//function prototypes:
void collectHeaderInfo(Image *image);