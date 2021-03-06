#include "grayscale.h"
#include "histogram.h"
#include "steganography.h"
#include "utils.h"

#define WRONG_NUMBER_OF_ARGUMENTS -2

int main(int argc, char *argv[])
{

    switch (argc)
    {
    case 2:
        char c;
        printf("0. Show file stats\n1. Decode steganography\n");
        scanf("%c", &c);
        if (c == '0')
        {
            return histProgram(argv[1]);
        }
        else if (c == '1')
        {
            return decodeSteganography(argv[1]);
        }

    case 3:
        return grayscaleProgram(argv[1], argv[2]);

    case 4:
        return encodeSteganography(argv[1], argv[2], argv[3]);

    default:
        printf("Wrong number of arguments!");
        return WRONG_NUMBER_OF_ARGUMENTS;
    }

    return EXIT_FAILURE;
}