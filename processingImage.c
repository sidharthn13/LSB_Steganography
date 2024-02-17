#include "typeDefinitions.h"
void displayImageData(Image *image){
    printf("the type of file is : %s\n",image->fileType);
    printf("the pixel array offset is : %d\n",image->pixelArrayOffset);
    printf("the width is : %d pixels\n",image->width);
    printf("number of bits per pixel is : %hu \n",image->bitsPerPixel);
    printf("size of raw pixel bitmap is : %d bytes\n",image->size);
}
void main(){
    Image image;
    collectHeaderInfo(&image);
    displayImageData(&image);
    fseek(image.fileStream, 54, SEEK_SET);  //moving the filestream pointer to the location where pixel data is stored
    
    uchar pixelBuffer;    //buffer for reading data
    uchar updatedPixel;   //buffer for writing data

    // //read data from all pixels
    // int count = 0;
    // while(ftell(image.fileStream)<2359350){
    //     count++;
    //     fread(&pixelBuffer, sizeof(uchar), 1, image.fileStream);
    //     printf("%d [%d]-> ",pixelBuffer,count);
    // }
    // fclose(image.fileStream);


    while(ftell(image.fileStream)<(image.size+image.pixelArrayOffset)){
        //looping condition : while the filestream pointer is less than total number of bytes in image file, continue to execute 
        fread(&pixelBuffer, sizeof(uchar), 1, image.fileStream);
        fseek(image.fileStream, -1, SEEK_CUR);
        if(pixelBuffer>=150){
            updatedPixel=255;
            fwrite(&updatedPixel, sizeof(uchar), 1, image.fileStream);
        }
        else{
        fseek(image.fileStream, 1, SEEK_CUR);
        }
    }
    fclose(image.fileStream);
}