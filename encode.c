#include "typeDefinitions.h"
void embedMagicString(Image *image){
    uchar imageByteValue=0;
    fseek(image->fileStream, -1*(sizeof(MAGIC_STRING)-1)*8, SEEK_END); //moving the file-stream ptr to embed magic str at the end of image
    for(int i = 0; i < sizeof(MAGIC_STRING)-1; i++){
        for(int j = 7; j>=0; j--){
            int bit = MAGIC_STRING[i] >> j & 1;
            fread(&imageByteValue, sizeof(uchar), 1, image->fileStream);
            fseek(image->fileStream, -1, SEEK_CUR);
            if(bit == 0){
                imageByteValue = (imageByteValue >> 1)<<1;
            }
            else{
                imageByteValue = (imageByteValue | 1);
            }
            fwrite(&imageByteValue, sizeof(uchar), 1, image->fileStream);
        }
    }
    printf("Magic string has been embedded successfully.\n");
}
int encode(Secret *secret, Image *image){
    int decryptCount = 0;  //indicates the number of bytes in which data has been embedded in the .bmp file
    fseek(image->fileStream, 58, SEEK_SET); //the first 4 bytes of the pixel data is reserved for decrypt counter
    fseek(secret->fileStream, 0, SEEK_SET);
    uchar charFromSecret;  //buffer to store data read from secret file
    uchar imageByteValue = 0;      //buffer to read and write data from image file
    while(ftell(image->fileStream) < (secret->size*8)+58 ){
        fread(&charFromSecret, sizeof(uchar), 1, secret->fileStream);
        for(int i = 7; i >= 0; i--){  //loop initialized to extract each bit from the character data byte
            int bit = ( charFromSecret >> i ) & 1 ;
            fread(&imageByteValue, sizeof(uchar), 1, image->fileStream);
            fseek(image->fileStream, -1, SEEK_CUR);
            if(bit == 0){
                imageByteValue = (imageByteValue >> 1)<<1;
            }
            else{
                imageByteValue = (imageByteValue | 1);
            }
            size_t numByteModified = fwrite(&imageByteValue, sizeof(uchar), 1, image->fileStream); //extracted bit is hidden in the LSB of one byte in pixel array
            decryptCount++; 

            #ifdef LOG_ENCODE  //the following line is used to check if the correct data has been written to the image file
                checkEncodeStatus(decryptCount ,imageByteValue,bit, numByteModified);  
            #endif
        }
    }
    embedMagicString(image);
    fseek(image->fileStream,54,SEEK_SET);
    fwrite(&decryptCount, sizeof(int), 1, image->fileStream);
    fclose(secret->fileStream);
    fclose(image->fileStream);
    printf("Success : Secret information has been embedded successfully.\n");
    return decryptCount;
}
