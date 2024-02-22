#include "typeDefinitions.h"
void decodeMagicString(Image *image){
    char *decodedMagic = (char *)malloc(sizeof(MAGIC_STRING));
    fseek(image->fileStream, -1*(sizeof(MAGIC_STRING)-1)*8, SEEK_END); //moving the file-stream ptr to embed magic str at the end of image
    int decodeLimit = 0;
    uchar hiddenChar = 0;
    uchar charBuffer;
    int count = 0;
    while(decodeLimit < (sizeof(MAGIC_STRING)-1)*8){
        hiddenChar = hiddenChar << 1;
        fread(&charBuffer, sizeof(uchar), 1, image->fileStream);
        uchar lsb = charBuffer & 1;
        if (lsb == 1){
            hiddenChar= hiddenChar | 1;
        }
        decodeLimit++;
        if(decodeLimit%8 == 0){
            decodedMagic[count]=(char)hiddenChar;
            count++;
            hiddenChar = 0;
        }
    }
    decodedMagic[sizeof(MAGIC_STRING)-1] = '\0';
    int result = strcmp(decodedMagic, MAGIC_STRING);
    free(decodedMagic);
    if(result!=0)  //if magic string not found, the program is terminated.
    { 
        fprintf(stderr, "Error : No data has been embedded in the image.\n");
        exit(0);
    }
     printf("Magic string decoded. Image is steged.\n");
}
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
            hiddenCharacter = 0;
        }
    }
    printf("Success : Secret message extracted to output file.\n");
    fclose(output->fileStream);
    fclose(image->fileStream);
    return decodeLimit;
}
