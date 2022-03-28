#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;
typedef int32_t LONG;

// https://docs.microsoft.com/en-us/windows/win32/api/wingdi/ns-wingdi-bitmapfileheader
typedef struct tagBITMAPFILEHEADER {
  WORD  bfType;
  DWORD bfSize;
  WORD  bfReserved1;
  WORD  bfReserved2;
  DWORD bfOffBits;
} BITMAPFILEHEADER, *LPBITMAPFILEHEADER, *PBITMAPFILEHEADER;

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

LPBITMAPFILEHEADER readFileHeader(FILE *file);
void printFileHeader(LPBITMAPFILEHEADER header);

LPBITMAPINFOHEADER readInfoHeader(FILE *file);
void printInfoHeader(LPBITMAPINFOHEADER infoHeader);

#define NUM_COLORS 3
#define NUM_HIST_ROWS 16

typedef int* COLOR;
typedef COLOR* HISTOGRAM;

HISTOGRAM histInit(void);
void freeHist(HISTOGRAM h);

void readPixel(HISTOGRAM h, FILE* file);
void readRow(HISTOGRAM h, LPBITMAPINFOHEADER infoHeader, FILE* file);
void readFile(HISTOGRAM h, LPBITMAPINFOHEADER InfoHeader, FILE* file);
#define STEP 256/NUM_HIST_ROWS
void printHistogram(HISTOGRAM h, float numPixels);