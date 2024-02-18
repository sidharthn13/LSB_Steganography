#include "typeDefinitions.h"

void main(){
    Secret file;
    FILE *ptr = fopen("test.txt","rb+");
    uchar *buffer = (uchar *)malloc(sizeof(uchar));
    fseek(ptr,0,SEEK_END);
    uint fileSize = ftell(ptr);
    printf("the size of the txt file is: %d bytes\n",fileSize);
    fseek(ptr,0,SEEK_SET);
    while(!feof(ptr)){
        fread(buffer, sizeof(uchar),1,ptr);
        printf("%c",*buffer);
    }
    printf("\n");
    
    fseek(ptr,0,SEEK_SET);
    uchar ch = 49;
    while(ftell(ptr)<fileSize){              //feof() cannot be used for write operations as there is no inherent eof when it comes to write operations 
        fwrite(&ch,sizeof(ch),1,ptr);
        // fseek(ptr,1,SEEK_CUR);            //there is no need to increment this as the fwrite function does it by itself
    }
    fclose(ptr);

}