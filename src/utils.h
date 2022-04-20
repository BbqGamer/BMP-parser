#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#define NUM_COLORS 3

//ERROR CODES
#define FILE_NOT_FOUND -1

//STRUCTURES
typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

#pragma pack(push, 1)
// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
// https://docs.microsoft.com/pl-pl/previous-versions/dd183376(v=vs.85)
typedef struct tagBITMAPINFOHEADER {
  DWORD biSize;
  LONG  biWidth;
  LONG  biHeight;
  WORD  biPlanes;
  WORD  biBitCount;
  DWORD biCompression;
  DWORD biSizeImage;
  LONG  biXPelsPerMeter;
  LONG  biYPelsPerMeter;
  DWORD biClrUsed;
  DWORD biClrImportant;
} BITMAPINFOHEADER, *LPBITMAPINFOHEADER, *PBITMAPINFOHEADER;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct tagPIXEL {
  BYTE b;
  BYTE g;
  BYTE r;
} PIXEL;
#pragma pack(pop)

typedef struct tagBitmap {
  LPBITMAPFILEHEADER fileHeader;
  LPBITMAPINFOHEADER infoHeader;
  BYTE* pixels;
} BMP;


void readBitmap(FILE* file, BMP* bmpPtr);
void freeBitmap(BMP* bmpPtr);

void readHeaders(FILE* file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER InfoHeader);
void readPixels(FILE* file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER infoHeader, BYTE** pixels);

void writeInfoHeader(FILE* file, LPBITMAPINFOHEADER infoHeader);
void writeFileHeader(FILE* file, LPBITMAPFILEHEADER header);

void printHeaders(BMP* bmpPtr);
void printFileHeader(LPBITMAPFILEHEADER header);
void printInfoHeader(LPBITMAPINFOHEADER infoHeader);


#endif