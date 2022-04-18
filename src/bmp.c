#include "utils.h"
#include "histogram.h"
#include "grayscale.h"
#include "steganography.h"

#define WRONG_NUMBER_OF_ARGUMENTS -2

int main(int argc, char* argv[]) {
    if(argc == 2) {
        char c;
        printf("0. Show file stats\n1. Decode steganography\n");
        scanf("%c", &c);
        if(c == '0') {
            return histProgram(argv[1]);
        } else if (c == '1') {
            return decodeSteganography(argv[1]);
        }
        return 0;
    } else if (argc == 3) {
        return grayscaleProgram(argv[1], argv[2]);
    } else if (argc == 4) {
        return encodeSteganography(argv[1], argv[2], argv[3]);
    } else {
       return WRONG_NUMBER_OF_ARGUMENTS;
    }

    return 0;
}