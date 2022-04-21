#ifndef UTILS_H
#define UTILS_H

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_COLORS 3

// ERROR CODES
#define FILE_NOT_FOUND -1

// STRUCTURES
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

#pragma pack(push, 1)
// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
typedef struct tagBITMAPFILEHEADER
{
    WORD bfType;
    DWORD bfSize;
    WORD bfReserved1;
    WORD bfReserved2;
    DWORD bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
// https://docs.microsoft.com/pl-pl/previous-versions/dd183376(v=vs.85)
typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;
    LONG biWidth;
    LONG biHeight;
    WORD biPlanes;
    WORD biBitCount;
    DWORD biCompression;
    DWORD biSizeImage;
    LONG biXPelsPerMeter;
    LONG biYPelsPerMeter;
    DWORD biClrUsed;
    DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagPIXEL
{
    BYTE b;
    BYTE g;
    BYTE r;
} PIXEL;
#pragma pack(pop)

typedef struct tagBitmap
{
    LPBITMAPFILEHEADER fileHeader;
    LPBITMAPINFOHEADER infoHeader;
    BYTE *pixels;
} BMP;

// READING FUNCTIONS
void readBitmap(FILE *file, BMP *bmpPtr);
void readHeaders(FILE *file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER InfoHeader);
void readPixels(FILE *file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER infoHeader, BYTE **pixels);

// FREEING FUNCTION
void freeBitmap(BMP *bmpPtr);

// WRITING FUNCTIONS
void writeBitmap(FILE *file, BMP *bmpPtr);
void writeHeaders(FILE *file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER infoHeader);
void writePixels(FILE *file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER infoHeader, BYTE *pixels);

// PRINTING FUNCTIONS
void printHeaders(BMP *bmpPtr);
void printFileHeader(LPBITMAPFILEHEADER header);
void printInfoHeader(LPBITMAPINFOHEADER infoHeader);

#endif