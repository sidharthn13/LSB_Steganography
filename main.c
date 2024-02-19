#include "typeDefinitions.h"
void main(){
    Image image;  //setting up data structure to store image data
    Secret secret;//setting up data structure to store secret file data
    collectHeaderInfo(&image);
    fseek(image.fileStream, image.pixelArrayOffset, SEEK_SET);  //moving the file-stream pointer to the location where pixel data is stored
    uchar pixelBuffer;    //buffer for reading data
    uchar updatedPixel;   //buffer for writing data
    collectSecretFileInfo(&secret);

    #ifdef LOG_CONFIG
    displayImageData(&image);   //if LOG macro is defined in the header file, display image header data
    #endif

    int encodeResult = encode(&secret, &image);
    printf("the number of bytes in which data has been embedded in .bmp file : %d bytes\n", encodeResult);
    int decodeResult = decode(&image);
    printf("the number of bytes in which data has been embedded in .bmp file : %d bytes\n", decodeResult);

    // while(ftell(image.fileStream)<(image.pixelArraySize+image.pixelArrayOffset)){
    //     //looping condition : while the file-stream pointer is less than total number of bytes in image file, continue to execute 
    //     fread(&pixelBuffer, sizeof(uchar), 1, image.fileStream);
    //     fseek(image.fileStream, -1, SEEK_CUR);
    //     if(pixelBuffer>=150){
    //         updatedPixel=255;
    //         fwrite(&updatedPixel, sizeof(uchar), 1, image.fileStream);
    //     }
    //     else{
    //     fseek(image.fileStream, 1, SEEK_CUR);
    //     }
    // }
    // fclose(image.fileStream);
}