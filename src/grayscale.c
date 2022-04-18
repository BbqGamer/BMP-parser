#include "grayscale.h"
#include "utils.h"

int grayscaleProgram(char* inFilename, char* outFilename) {
    FILE* in = fopen(inFilename, "rb");
    if(in == NULL) {
        printf("Error opening input file!");
        return FILE_NOT_FOUND;
    }

    FILE* out = fopen(outFilename, "wb");
    if(out == NULL) {
        printf("Error opening output file!");
        fclose(in);
        return FILE_NOT_FOUND;
    }

    LPBITMAPFILEHEADER header = readFileHeader(in);
    LPBITMAPINFOHEADER infoHeader = readInfoHeader(in);
    writeFileHeader(out, header);
    writeInfoHeader(out, infoHeader);

    fclose(in);
    fclose(out);
}