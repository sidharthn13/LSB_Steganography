#include "typeDefinitions.h"
int decode(Image *image, Output *output){
    int decodeLimit; //the number of bytes from  which LSb data have to be extracted
    uchar pixelDataBuffer;//buffer to store data read from bytes in the pixel data array
    uchar hiddenCharacter=0;//buffer used to store the bits extracted from every 8 bytes
    int numBytesRead=0;//to keep track of how many bytes have been read from the pixel array 
    fseek(image->fileStream, 54, SEEK_SET);
    fread(&decodeLimit, sizeof(int), 1, image->fileStream);
    // uint currentPosition = ftell(image->fileStream);
    while( numBytesRead < decodeLimit ){
        hiddenCharacter = hiddenCharacter << 1;
        fread(&pixelDataBuffer, sizeof(uchar), 1, image->fileStream);
        uchar lsb = pixelDataBuffer & 1;
        if(lsb == 1){
            hiddenCharacter = hiddenCharacter | 1;
        }
        numBytesRead++;
        if(numBytesRead % 8 == 0){
            fwrite(&hiddenCharacter, sizeof(uchar), 1, output->fileStream);
            printf("%c",hiddenCharacter);
            hiddenCharacter = 0;
        }
    }
    printf("\n");
    return decodeLimit;
}
