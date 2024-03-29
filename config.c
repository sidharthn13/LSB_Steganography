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
void collectHeaderInfo(Image *image, char *pathOfFile){
    image->fileStream = fopen(pathOfFile,"rb+"); //setting up the file stream pointer for image file
    if(image->fileStream==NULL){
        fprintf(stderr, "Error : Error opening file. Please make sure you have provided the correct path and if file exists\n");
        exit(70);
    }
    fgets(image->fileType,3,image->fileStream); //collecting file type info 
    if(strcmp(image->fileType, "BM")!=0){
        fprintf(stderr,"Error : The file provided is not a .bmp file");
        exit(65);
    }
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
void collectSecretFileInfo(Secret *secret, char *pathOfFile){
    if(pathOfFile==NULL){    //if command line argument for the path of image file is empty
        fprintf(stderr, "Error : Path to file containing secret file not provided.\n");
        exit(70);}
    secret->fileStream = fopen("secret.txt","rb+");  //setting up file stream pointer for secret file
    if(secret->fileStream==NULL){
        fprintf(stderr, "Error : Error opening file. Please make sure you have provided the correct path and if file exists\n");
        exit(70);
    }
    fseek(secret->fileStream,0,SEEK_END);  
    secret->size = ftell(secret->fileStream); //collecting size data of secret file 
    fseek(secret->fileStream, 0, SEEK_SET); 
}
void checkImgCapacity(Secret *secret, Image *image){
    if((image->pixelArraySize-4-(sizeof(MAGIC_STRING)*8)) < secret->size)   //4 bytes used to store number of image bytes taken for embedding, 24 bytes used to store magic string
    {
        fprintf(stderr, "Error : Provided secret message is too big to be embedded in image.\n");
        exit(0);
    }
}
void initOutputFile(Output *output, char *pathOfFile){
    if(pathOfFile==NULL){                                //If file name is not provided, file with default name is created
        output->fileStream = fopen("output.txt","w");  //setting up the output file in write mode(create file if not present, truncate existing data)
        if(output->fileStream == NULL){
            fprintf(stderr, "Error : Cannot create output file.\n");
            exit(70);
        }
        printf("Output file created.\n");
    }
    else{
        output->fileStream = fopen(pathOfFile,"w");
        if(output->fileStream == NULL){
            fprintf(stderr, "Error : Cannot create output file.\n");
            exit(70);
        }
        printf("Output file, %s created.\n", pathOfFile);
    }
    }
   

