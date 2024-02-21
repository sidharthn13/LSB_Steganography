#include "typeDefinitions.h"
void main(int argc, char *argv[]){
    int checkCla = checkClaOption(argc, argv);  //used to check command line argument option
    Image image;  //setting up data structure to store image data
    collectHeaderInfo(&image,argv[2]);
    if(checkCla == 1){
        Secret secret; //setting up data structure to store secret file data
        collectSecretFileInfo(&secret, argv[3]);
        #ifdef LOG_IMAGE_CONFIG
            displayImageData(&image);   //if LOG macro is defined in the header file, display image header data
        #endif
        encode(&secret, &image);
    }
    else{
    Output output; //setting up data structure to store output file-stream ptr
    initOutputFile(&output, argv[3]);
    decode(&image, &output);
    }
}