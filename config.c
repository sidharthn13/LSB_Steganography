#include "typeDefinitions.h"
void collectHeaderInfo(Image *image){
    image->fileStream = fopen("beautiful.bmp","rb+"); //setting up the file stream pointer
    fgets(image->fileType,3,image->fileStream); //collecting file type info 
    fseek(image->fileStream,8,SEEK_CUR);
    fread(&(image->pixelArrayOffset), sizeof(uint), 1, image->fileStream); //collecting offset after which pixel data is present
    fseek(image->fileStream,4,SEEK_CUR);  //moving the file stream pointer to offset where data about width is present
    fread(&(image->width), sizeof(uint), 1, image->fileStream);  //collecting width data
    fseek(image->fileStream,6,SEEK_CUR);
    fread(&image->bitsPerPixel, sizeof(usint), 1, image->fileStream);
    fseek(image->fileStream,4,SEEK_CUR);
    fread(&image->size, sizeof(uint), 1, image->fileStream);
}