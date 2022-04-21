#include "utils.h"

// READING FUNCTIONS
void readBitmap(FILE *file, BMP *bmpPtr)
{
    bmpPtr->fileHeader = (BITMAPFILEHEADER *)malloc(sizeof(BITMAPFILEHEADER));
    bmpPtr->infoHeader = (BITMAPINFOHEADER *)malloc(sizeof(BITMAPINFOHEADER));
    readHeaders(file, bmpPtr->fileHeader, bmpPtr->infoHeader);
    readPixels(file, bmpPtr->fileHeader, bmpPtr->infoHeader, &(bmpPtr->pixels));
}

void readHeaders(FILE *file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER InfoHeader)
{
    fread(fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fread(InfoHeader, sizeof(BITMAPINFOHEADER), 1, file);
}

void readPixels(FILE *file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER infoHeader, BYTE **pixels)
{
    DWORD bytesPerPixel = ((DWORD)infoHeader->biBitCount) / 8;
    int paddedRowSize = ((infoHeader->biBitCount * infoHeader->biWidth + 31) / 32) * 4;
    int unpaddedRowSize = infoHeader->biWidth * bytesPerPixel;
    int totalSize = unpaddedRowSize * infoHeader->biHeight;
    *pixels = (BYTE *)malloc(totalSize);
    int i = 0;
    BYTE *currentRowPointer = *pixels + ((infoHeader->biHeight - 1) * unpaddedRowSize);
    for (i = 0; i < infoHeader->biHeight; i++)
    {
        fseek(file, fileHeader->bfOffBits + (i * paddedRowSize), SEEK_SET);
        fread(currentRowPointer, 1, unpaddedRowSize, file);
        currentRowPointer -= unpaddedRowSize;
    }
}

// FREE FUNCTION
void freeBitmap(BMP *bmpPtr)
{
    free(bmpPtr->fileHeader);
    free(bmpPtr->infoHeader);
    free(bmpPtr->pixels);
    free(bmpPtr);
}

// WRITING FUNCTIONS
void writeBitmap(FILE *file, BMP *bmpPtr)
{
    writeHeaders(file, bmpPtr->fileHeader, bmpPtr->infoHeader);
    writePixels(file, bmpPtr->fileHeader, bmpPtr->infoHeader, bmpPtr->pixels);
}

void writeHeaders(FILE *file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER infoHeader)
{
    fwrite(fileHeader, sizeof(BITMAPFILEHEADER), 1, file);
    fwrite(infoHeader, sizeof(BITMAPINFOHEADER), 1, file);
}

void writePixels(FILE *file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER infoHeader, BYTE *pixels)
{
    DWORD bytesPerPixel = ((DWORD)infoHeader->biBitCount) / 8;
    int paddedRowSize = ((infoHeader->biBitCount * infoHeader->biWidth + 31) / 32) * 4;
    int unpaddedRowSize = infoHeader->biWidth * bytesPerPixel;
    fseek(file, fileHeader->bfOffBits, SEEK_SET);
    // READ ONE ROW AND THEN NEXT
    fwrite(&pixels[(infoHeader->biHeight - 1) * unpaddedRowSize], 1, unpaddedRowSize, file);
    for (int i = 1; i < infoHeader->biHeight; i++)
    {
        int pixelOffset = ((infoHeader->biHeight - i) - 1) * unpaddedRowSize;
        fwrite(&pixels[pixelOffset], 1, paddedRowSize, file);
    }
}

// PRINTING FUNCTION
void printHeaders(BMP *bmpPtr)
{
    printFileHeader(bmpPtr->fileHeader);
    printInfoHeader(bmpPtr->infoHeader);
}

void printFileHeader(LPBITMAPFILEHEADER header)
{
    printf("BITMAPFILEHEADER:\n");
    printf("  bfType:\t0x%X (%s)\n", header->bfType, (header->bfType == 0x4D42) ? "BM" : "not a BMP\0");
    printf("  bfSize:\t%d\n", header->bfSize);
    printf("  bfReserved1:\t0x%x\n", header->bfReserved1);
    printf("  bfReserved2:\t0x%x\n", header->bfReserved2);
    printf("  bfOffBits:\t%d\n", header->bfOffBits);
    printf("\n");
}

void printInfoHeader(LPBITMAPINFOHEADER infoHeader)
{
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