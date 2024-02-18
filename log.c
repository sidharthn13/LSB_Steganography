#include "typeDefinitions.h"
void displayImageData(Image *image){
    printf("the type of file is : %s\n",image->fileType);
    printf("the pixel array offset is : %d\n",image->pixelArrayOffset);
    printf("the width is : %d pixels\n",image->width);
    printf("number of bits per pixel is : %hu \n",image->bitsPerPixel);
    printf("size of raw pixel bitmap is : %d bytes\n",image->pixelArraySize);
    printf("number of bytes that are used for 4-byte padding : %d bytes\n",image->padding);
}