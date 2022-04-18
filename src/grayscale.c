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

    fillGrayscale(infoHeader, in, out);

    fclose(in);
    fclose(out);
}

void fillGrayscale(LPBITMAPINFOHEADER infoHeader, FILE* in, FILE* out) {
    int lineSize = ((infoHeader->biBitCount * infoHeader->biWidth + 31)/32)*4;
    int sum;
    BYTE* buffer = (BYTE*)malloc(sizeof(BYTE)*lineSize);
    for(int i = 0; i < infoHeader->biHeight; i++) {
        fread(buffer, sizeof(BYTE), lineSize, in);
        for(int i = 0; i < infoHeader->biWidth; i++) {
            sum = 0;
            for(int j = 0; j < NUM_COLORS; j++) {
                sum += buffer[3*i+j];
            }
            for(int j = 0; j < NUM_COLORS; j++) {
                buffer[3*i+j] = sum/NUM_COLORS;
            }
        }
        fwrite(buffer, sizeof(BYTE), lineSize, out);
    }
    free(buffer);
}