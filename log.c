//Used to log info after important function calls. Can be used to debug the program
#include "typeDefinitions.h"
void displayImageData(Image *image){
    printf("the type of file is : %s\n",image->fileType);
    printf("the pixel array offset is : %d\n",image->pixelArrayOffset);
    printf("the width is : %d pixels\n",image->width);
    printf("number of bits per pixel is : %hu \n",image->bitsPerPixel);
    printf("size of raw pixel bitmap is : %d bytes\n",image->pixelArraySize);
    printf("number of bytes that are used for 4-byte padding : %d bytes\n",image->padding);
}
void checkEncodeStatus(int bytesToBeDecoded, uchar modifiedByteValue, int bit, size_t numBytesWritten){
    printf("value of byte %d is :%d....the bit embedded in the byte is : %d....byte update status: %zu\n",
     bytesToBeDecoded,modifiedByteValue,bit, numBytesWritten);  
} //numBytesWritten should have a value of 1. This indicates successful write operation on one byte.