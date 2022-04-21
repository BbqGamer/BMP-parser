#ifndef GRAYSCALE_H
#define GRAYSCALE_H
#include "utils.h"

int grayscaleProgram(char *inFilename, char *outFilename);
void turnToGrayscale(BMP* bitmap);
PIXEL pixelToGray(PIXEL pixel);

#endif