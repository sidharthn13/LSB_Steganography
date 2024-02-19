#include "typeDefinitions.h"
void main(){
    Image image;  //setting up data structure to store image data
    Secret secret; //setting up data structure to store secret file data
    Output output; //setting up data structure to store output file-stream ptr
    collectHeaderInfo(&image);
    fseek(image.fileStream, image.pixelArrayOffset, SEEK_SET);  //moving the file-stream pointer to the location where pixel data is stored
    uchar pixelBuffer;    //buffer for reading data
    uchar updatedPixel;   //buffer for writing data
    collectSecretFileInfo(&secret);
    initOutputFile(&output);

    #ifdef LOG_CONFIG
    displayImageData(&image);   //if LOG macro is defined in the header file, display image header data
    #endif

    encode(&secret, &image);
    decode(&image, &output);
}