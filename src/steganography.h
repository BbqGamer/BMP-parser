#ifndef STEGANOGRAPHY_H
#define STEGANOGRAPHY_H

#include "utils.h"

int decodeSteganography(char* file);
int encodeSteganography(char* in, char* out, char* message);

#endif