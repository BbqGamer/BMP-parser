#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "utils.h"

int histProgram(char* filename);

typedef struct COLOR_COUNTERtag {
    int* r;
    int* g;
    int* b;
} COLOR_COUNT;

#define NUM_HIST_ROWS 16
#define STEP (256/NUM_HIST_ROWS)

COLOR_COUNT* counterInit(void);
void freeCounter(COLOR_COUNT* c);
void fillCounter(COLOR_COUNT* c, BMP* bitmap, FILE* file);
void printHistogram(COLOR_COUNT* c, float numPixels);

#endif