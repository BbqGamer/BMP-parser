#include "steganography.h"

int decodeSteganography(char *file)
{
    printf("READ");
    return 0;
}

int encodeSteganography(char *inFilename, char *outFilename, char *message)
{
    //     FILE* in = fopen(inFilename, "rb");
    //     if(in == NULL) {
    //         printf("Error opening input file!");
    //         return FILE_NOT_FOUND;
    //     }

    //     FILE* out = fopen(outFilename, "wb");
    //     if(out == NULL) {
    //         printf("Error opening output file!");
    //         fclose(in);
    //         return FILE_NOT_FOUND;
    //     }

    //     BITMAPFILEHEADER header;
    //     readFileHeader(in, &header);

    //     BITMAPINFOHEADER infoHeader;
    //     readInfoHeader(in, &infoHeader);

    //     // writeFileHeader(out, header);
    //     // writeInfoHeader(out, infoHeader);

    //     //encodeMessage(in, out, message, infoHeader);

    //     fclose(in);
    //     fclose(out);

    //     return 0;
    // }

    // void encodeMessage(FILE* in, FILE* out, char* message, LPBITMAPINFOHEADER infoHeader) {
    //     int l = strlen(message);
    //     int c = 0;

    //     int lineSize = ((infoHeader->biBitCount * infoHeader->biWidth + 31) / 32) * 4;
    //     int sum;

    //     BYTE* buffer = (BYTE*)malloc(sizeof(BYTE)*lineSize);
    //     for(int i = 0; i < infoHeader->biHeight; i++) {
    //         fread(buffer, sizeof(BYTE), lineSize, in);

    //         for(int i = 0; i < infoHeader->biWidth; i+=8) {
    //             if(c < l) {
    //                 buffer[i] = 100;
    //                 //encodeChar(buffer, i, message[c]);
    //             }
    //             c++;
    //         }

    //         fwrite(buffer, sizeof(BYTE), lineSize, out);
    //     }
    //     free(buffer);
    return 0;
}

void encodeChar(BYTE *buffer, int index, char c)
{
    int mask = 0xFE;
    char bit;

    for (int i = 0; i < 8; i++)
    {
        bit = c & 1;

        buffer[index + i] = (buffer[index + i] & mask) + bit;

        c = c >> 1;
    }
}