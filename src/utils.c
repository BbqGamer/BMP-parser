#include "utils.h"

LPBITMAPFILEHEADER readFileHeader(FILE *file) {
    LPBITMAPFILEHEADER header = (LPBITMAPFILEHEADER)malloc(sizeof(BITMAPFILEHEADER));
    
    WORD bufferW;
    DWORD bufferDW;

    fread(&bufferW, sizeof(WORD), 1, file);
    header->bfType = bufferW;

    fread(&bufferDW, sizeof(DWORD), 1, file);
    header->bfSize = bufferDW;

    fread(&bufferW, sizeof(WORD), 1, file);
    header->bfReserved1 = bufferW;

    fread(&bufferW, sizeof(WORD), 1, file);
    header->bfReserved2 = bufferW;

    fread(&bufferDW, sizeof(DWORD), 1, file);
    header->bfOffBits = bufferDW;

    return header;
}

void printFileHeader(LPBITMAPFILEHEADER header) {
    printf("BITMAPFILEHEADER:\n");
    printf("  bfType:\t0x%X (%s)\n", header->bfType, (header->bfType == 0x4D42) ? "BM" : "not a BMP\0");
    printf("  bfSize:\t%d\n", header->bfSize);
    printf("  bfReserved1:\t0x%x\n", header->bfReserved1);
    printf("  bfReserved2:\t0x%x\n", header->bfReserved2);
    printf("  bfOffBits:\t%d\n", header->bfOffBits);
    printf("\n");
}


LPBITMAPINFOHEADER readInfoHeader(FILE *file) {
    LPBITMAPINFOHEADER infoHeader = (LPBITMAPINFOHEADER)malloc(sizeof(BITMAPINFOHEADER));
    
    WORD bufferW;
    DWORD bufferDW;
    LONG bufferL;

    fread(&bufferDW, sizeof(DWORD), 1, file);
    infoHeader->biSize = bufferDW;

    fread(&bufferL, sizeof(LONG), 1, file);
    infoHeader->biWidth = bufferL;

    fread(&bufferL, sizeof(LONG), 1, file);
    infoHeader->biHeight = bufferL;

    fread(&bufferW, sizeof(WORD), 1, file);
    infoHeader->biPlanes = bufferW;

    fread(&bufferW, sizeof(WORD), 1, file);
    infoHeader->biBitCount = bufferW;
    
    fread(&bufferDW, sizeof(DWORD), 1, file);
    infoHeader->biCompression = bufferDW;

    fread(&bufferDW, sizeof(DWORD), 1, file);
    infoHeader->biSizeImage = bufferDW;

    fread(&bufferL, sizeof(LONG), 1, file);
    infoHeader->biXPelsPerMeter = bufferL;

    fread(&bufferL, sizeof(LONG), 1, file);
    infoHeader->biYPelsPerMeter = bufferL;

    fread(&bufferDW, sizeof(DWORD), 1, file);
    infoHeader->biClrUsed = bufferDW;

    fread(&bufferDW, sizeof(DWORD), 1, file);
    infoHeader->biClrImportant = bufferDW;

    return infoHeader;
}

void printInfoHeader(LPBITMAPINFOHEADER infoHeader) {
    printf("BITMAPINFOHEADER:\n");
    printf("  biSize:\t   %d\n", infoHeader->biSize);
    printf("  biWidth:\t   %d\n", infoHeader->biWidth);
    printf("  biHeight:\t   %d\n", infoHeader->biHeight);
    printf("  biPlanes:\t   %d\n", infoHeader->biPlanes);
    printf("  biBitCount:\t   %d\n", infoHeader->biBitCount);
    printf("  biCompression:   %d\n", infoHeader->biCompression);
    printf("  biSizeImage:\t   %d\n", infoHeader->biSizeImage);
    printf("  biXPelsPerMeter: %d\n", infoHeader->biXPelsPerMeter);
    printf("  biYPelsPerMeter: %d\n", infoHeader->biYPelsPerMeter);
    printf("  biClrUsed:\t   %d\n", infoHeader->biClrUsed);
    printf("  biClrImportant:  %d\n", infoHeader->biClrImportant);
}