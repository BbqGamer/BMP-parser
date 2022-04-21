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
    writeBitmap(out, bitmap);

    // CLEANUP
    freeBitmap(bitmap);
    fclose(in);
    fclose(out);
    return 0;
}

// void fillGrayscale(LPBITMAPINFOHEADER infoHeader, FILE* in, FILE* out) {
//     int lineSize = ((infoHeader->biBitCount * infoHeader->biWidth + 31) / 32) * 4;

//     BYTE* buffer = (BYTE*)malloc(sizeof(BYTE)*lineSize);

//     for(int i = 0; i < infoHeader->biHeight; i++) {
//         fread(buffer, sizeof(BYTE), lineSize, in);

//         // for(int i = 0; i < infoHeader->biWidth; i++) {
//         //     BYTE gray = (BYTE)((buffer[i*3] + buffer[i*3+1] + buffer[i*3+2]) / 3);
//         //     buffer[i*3] = buffer[i*3+1] = buffer[i*3+2] = gray;
//         // }
//         fwrite(buffer, sizeof(BYTE), lineSize, out);
//     }
//     free(buffer);
// }