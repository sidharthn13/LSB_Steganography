#include "typeDefinitions.h"

void main(){
    Secret file;
    FILE *ptr = fopen("test.txt","r+");
    char *buffer = (char *)malloc(sizeof(char));
    fseek(ptr,0,SEEK_END);
    uint fileSize = ftell(ptr);
    printf("the size of the txt file is: %d bytes\n",fileSize);
    fseek(ptr,0,SEEK_SET);
    while(!feof(ptr)){
        fread(buffer, sizeof(char),1,ptr);
        printf("%c",*buffer);
    }
    printf("\n");
    
    fseek(ptr,0,SEEK_SET);
    char ch = 'o';
    while(ftell(ptr)<fileSize){              //feof() cannot be used for write operations as there is no inherent eof when it comes to write operations 
        fwrite(&ch,sizeof(ch),1,ptr);
        // fseek(ptr,1,SEEK_CUR);            //there is no need to increment this as the fwrite function does it by itself
    }
    fclose(ptr);

}