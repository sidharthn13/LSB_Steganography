#include "typeDefinitions.h"
int encode(Secret *secret, Image *image){
    int decryptCount = 0;  //indicates the number of bytes in which data has been embedded in the .bmp file
    fseek(image->fileStream, 58, SEEK_SET); //the first 4 bytes of the pixel data is reserved for decrypt counter
    fseek(secret->fileStream, 0, SEEK_SET);
    uchar charFromSecret;  //buffer to store data read from secret file
    uchar pixelValue = 0;      //buffer to read and write data from image file
    while(ftell(secret->fileStream) < secret->size){
        fread(&charFromSecret, sizeof(uchar), 1, secret->fileStream);
        for(int i = 7; i >= 0; i--){
            int bit = ( charFromSecret >> i ) & 1 ;
            fread(&pixelValue, sizeof(uchar), 1, image->fileStream);
            fseek(image->fileStream, -1, SEEK_CUR);
            if(bit == 0){
                pixelValue = (pixelValue >> 1)<<1;
            }
            else{
                pixelValue = (pixelValue | 1);
            }
            fwrite(&pixelValue, sizeof(uchar), 1, image->fileStream);
            decryptCount++;
        }
    }
    fseek(image->fileStream,54,SEEK_SET);
    fwrite(&decryptCount, sizeof(int), 1, image->fileStream);
    return decryptCount;
}
