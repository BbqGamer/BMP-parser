#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include "utils.h"

int decodeSteganography(char *file);

int encodeSteganography(char *inFilename, char *outFilename, char *message);
void encodeMessage(FILE *in, FILE *out, char *message, LPBITMAPINFOHEADER infoHeader);
void encodeChar(BYTE *buffer, int index, char c);

#endif