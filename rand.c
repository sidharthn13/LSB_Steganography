#include <stdio.h>
#include <stdlib.h>
#include<string.h>

void greet(char *string){
    printf("greetings %s\n", string);
}
void fuck(char *string){
    printf("fuck off %s\n",string);
}
int hashing(char *string){
    int index = 0;
    for(int i = 0; i < strlen(string); i++){
        int asciiVal = (int)string[i];
        index+=asciiVal;
    }
    return index-145;
}

void main(int argc, char* argv[]){
    // void (*functionP[2])(char *string);
    // functionP[0] = &greet;
    // functionP[1] = &fuck;
    // // printf("the hashed value of '-e' is : %d\n", hashing("-e"));
    // // printf("the hashed value of '-d' is : %d\n", hashing("-d"));
    
    // if(argc == 3){
    //     int index = hashing(argv[1]);
    //     functionP[index](argv[2]);
    // }

    // functionP[3]("sid");

    // if(argc==4){
    //     if(strcmp(argv[1],"-e")==0){
    //     printf("encode option selected");
    //     }
    //     else{
    //         printf("improper option");
    //     }
    // }
    // else if(argc==3){
    //     if(strcmp(argv[1],"-d")==0){
    //         printf("decode option selected");
    //     }
    //     else{
    //         printf("improper option usage");
    //     }
    // }
    // else{
    //     printf("invalid number of arguments passed");
    // }
    if(argv[1]==NULL){fprintf(stderr, "no file argument passed\n");}
    FILE *filePtr = fopen(argv[1],"r");
    if(filePtr == NULL){
        fprintf(stderr,"failed to open file.");
        exit(70);
    }

}