#ifndef GRAYSCALE_H
#define GRAYSCALE_H
#include "utils.h"

int grayscaleProgram(char *inFilename, char *outFilename);
void fillGrayscale(LPBITMAPINFOHEADER infoHeader, FILE *in, FILE *out);

#endif