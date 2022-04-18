#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "utils.h"

#define NUM_HIST_ROWS 16
typedef int* COLOR;
typedef COLOR* HISTOGRAM;

int histProgram(char* filename);

HISTOGRAM histInit(void);
void freeHist(HISTOGRAM h);
void fillHist(HISTOGRAM h, LPBITMAPINFOHEADER InfoHeader, FILE* file);

#define STEP 256/NUM_HIST_ROWS
void printHistogram(HISTOGRAM h, float numPixels);

#endif