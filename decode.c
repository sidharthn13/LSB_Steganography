#include "typeDefinitions.h"
uint decode(Image *image){
    uint decodeResult;
    fseek(image->fileStream, 54, SEEK_SET);
    fread(&decodeResult, sizeof(uint), 1, image->fileStream);
    return decodeResult;
}
