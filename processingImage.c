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
    uchar pixelBuffer;
    int count = 0;
    while(ftell(image.fileStream)<2359350){
        count++;
        fread(&pixelBuffer, sizeof(uchar), 1, image.fileStream);
        printf("%d [%d]-> ",pixelBuffer,count);
    }
    fclose(image.fileStream);
}