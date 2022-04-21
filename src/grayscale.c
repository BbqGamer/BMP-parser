#include "grayscale.h"
#include "utils.h"

int grayscaleProgram(char *inFilename, char *outFilename)
{
    FILE *in = fopen(inFilename, "rb");
    if (in == NULL)
    {
        printf("Error opening input file!");
        return FILE_NOT_FOUND;
    }

    FILE *out = fopen(outFilename, "wb");
    if (out == NULL)
    {
        printf("Error opening output file!");
        fclose(in);
        return FILE_NOT_FOUND;
    }

    // READ BITMAP
    BMP *bitmap = (BMP *)malloc(sizeof(BMP));
    readBitmap(in, bitmap);

    turnToGrayscale(bitmap);

    writeBitmap(out, bitmap);

    // CLEANUP
    freeBitmap(bitmap);
    fclose(in);
    fclose(out);
    return 0;
}

void turnToGrayscale(BMP* bitmap) {
    BYTE *ptr = bitmap->pixels;;
    for (int i = 0; i < bitmap->infoHeader->biWidth * bitmap->infoHeader->biHeight; i++)
    {
        PIXEL pixel;
        memcpy(&pixel, ptr, sizeof(PIXEL));
        pixel = pixelToGray(pixel); 
        memcpy(ptr, &pixel, sizeof(PIXEL));
       
        ptr += sizeof(PIXEL);
    }
}

PIXEL pixelToGray(PIXEL pixel) {
    PIXEL newPixel;
    newPixel.r = newPixel.g = newPixel.b = (pixel.r + pixel.g + pixel.b) / 3;
    return newPixel;
}
