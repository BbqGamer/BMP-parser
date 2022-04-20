#include "utils.h"

void readBitmap(FILE* file, BMP* bmpPtr) {
    bmpPtr->fileHeader = (BITMAPFILEHEADER*)malloc(sizeof(BITMAPFILEHEADER));
    bmpPtr->infoHeader = (BITMAPINFOHEADER*)malloc(sizeof(BITMAPINFOHEADER));
    readHeaders(file, bmpPtr->fileHeader, bmpPtr->infoHeader);
    readPixels(file, bmpPtr->fileHeader, bmpPtr->infoHeader, &(bmpPtr->pixels));
}

void freeBitmap(BMP* bmpPtr) {
    free(bmpPtr->fileHeader);
    free(bmpPtr->infoHeader);
    free(bmpPtr->pixels);
    free(bmpPtr);
}

void readHeaders(FILE* file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER InfoHeader) {
    fread(fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fread(InfoHeader, sizeof(BITMAPINFOHEADER), 1, file);
}

void printHeaders(BMP* bmpPtr) {
    printFileHeader(bmpPtr->fileHeader);
    printInfoHeader(bmpPtr->infoHeader);
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

void writeFileHeader(FILE* file, LPBITMAPFILEHEADER header) {
    WORD bufferW;
    DWORD bufferDW;
    fwrite(&header->bfType, sizeof(WORD), 1, file);
    fwrite(&header->bfSize, sizeof(DWORD), 1, file);
    fwrite(&header->bfReserved1, sizeof(WORD), 1, file);
    fwrite(&header->bfReserved2, sizeof(WORD), 1, file);
    fwrite(&header->bfOffBits, sizeof(DWORD), 1, file);
}

void readPixels(FILE* file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER infoHeader, BYTE** pixels) {
    DWORD bytesPerPixel = ((DWORD)infoHeader->biBitCount) / 8;
    int paddedRowSize = (int)(4 * ceil((float)(infoHeader->biWidth) / 4.0f))*bytesPerPixel;
    int unpaddedRowSize = infoHeader->biWidth * infoHeader->biBitCount;
    int totalSize = unpaddedRowSize* infoHeader->biHeight;
    *pixels = (BYTE*)malloc(totalSize);
    int i = 0;
    BYTE* currentRowPointer = *pixels+((infoHeader->biHeight-1)*unpaddedRowSize);
    for (i = 0; i < infoHeader->biHeight; i++)
    {
        fseek(file, fileHeader->bfOffBits+(i*paddedRowSize), SEEK_SET);
        fread(currentRowPointer, 1, unpaddedRowSize, file);
        currentRowPointer -= unpaddedRowSize;
    }
}