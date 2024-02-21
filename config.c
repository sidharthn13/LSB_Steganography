#include "typeDefinitions.h"
int checkClaOption(int claArgumentCount, char *claArgumentArr[]){
    if(claArgumentCount >= 3){
        if(strcmp(claArgumentArr[1], "-e") == 0 ){
            return 1;
        }
        else if(strcmp(claArgumentArr[1], "-d") == 0 ){
            return 2;
        }
        else{
            fprintf(stderr, "Error : Invalid Application command line option");
            exit(64);
        }        
    }
    else{
        fprintf(stderr, "Error : Insufficient number of command line arguments");
        exit(64);   //status code for command line usage error
    }
}
void collectHeaderInfo(Image *image){
    image->fileStream = fopen("beautiful.bmp","rb+"); //setting up the file stream pointer for image file
    fgets(image->fileType,3,image->fileStream); //collecting file type info 
    fseek(image->fileStream,8,SEEK_CUR);
    fread(&(image->pixelArrayOffset), sizeof(uint), 1, image->fileStream); //collecting offset after which pixel data is present
    fseek(image->fileStream,4,SEEK_CUR);  //moving the file stream pointer to offset where data about width is present
    fread(&(image->width), sizeof(uint), 1, image->fileStream);  //collecting width data
    fseek(image->fileStream,6,SEEK_CUR);
    fread(&image->bitsPerPixel, sizeof(usint), 1, image->fileStream);
    fseek(image->fileStream,4,SEEK_CUR);
    fread(&image->pixelArraySize, sizeof(uint), 1, image->fileStream);
    image->padding=( (image->width * (image->bitsPerPixel/8)) % 4 );  //finding the number of bytes that are used for padding the scan lines
    image->padding = (image->padding != 0) ? 4 - image->padding : 0;  
}
void collectSecretFileInfo(Secret *secret){
    secret->fileStream = fopen("secret.txt","rb+");  //setting up file stream pointer for secret file
    fseek(secret->fileStream,0,SEEK_END);  
    secret->size = ftell(secret->fileStream); //collecting size data of secret file 
    fseek(secret->fileStream, 0, SEEK_SET); 
}
void initOutputFile(Output *output){
    output->fileStream = fopen("output.txt","w");  //setting up the output file in write mode(create file if not present, truncate existing data)
}

