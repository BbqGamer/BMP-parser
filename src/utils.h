#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

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

typedef struct tagBitmap {
  BITMAPFILEHEADER fileHeader;
  BITMAPINFOHEADER infoHeader;
  BYTE* pixels;
} Bitmap, *BitmapPtr;

void readHeaders(FILE* file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER InfoHeader);
BYTE* readPixels(FILE* file, LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER InfoHeader);

void writeInfoHeader(FILE* file, LPBITMAPINFOHEADER infoHeader);
void writeFileHeader(FILE* file, LPBITMAPFILEHEADER header);

void printHeaders(LPBITMAPFILEHEADER fileHeader, LPBITMAPINFOHEADER infoHeader);
void printFileHeader(LPBITMAPFILEHEADER header);
void printInfoHeader(LPBITMAPINFOHEADER infoHeader);


#endif