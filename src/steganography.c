#include "steganography.h"

int decodeSteganography(char *file)
{
    FILE *in = fopen(file, "rb");
    if (in == NULL)
    {
        printf("Error opening input file!");
        return FILE_NOT_FOUND;
    }

    // READ BITMAP
    BMP *bitmap = (BMP *)malloc(sizeof(BMP));
    readBitmap(in, bitmap);

    decodeMessage(bitmap);

    // CLEANUP
    freeBitmap(bitmap);
    fclose(in);

    return 0;
}

void decodeMessage(BMP *bitmap)
{
    int l = decodeChar(bitmap->pixels, 0);
    char *message = (char *)malloc(sizeof(char) * l + 1);
    for (int i = 0; i < l; i++)
    {
        message[i] = decodeChar(bitmap->pixels, (i + 1) * 8);
    }
    message[l] = '\0';
    printf("%s\n", message);
    free(message);
}

char decodeChar(BYTE *buffer, int index)
{
    char c = 0;

    int mask = 0xFE;
    char bit;

    for (int i = 0; i < 8; i++)
    {
        c = c << 1;
        bit = buffer[index + 7 - i] & 1;
        c += bit;
    }
    return c;
}

int encodeSteganography(char *inFilename, char *outFilename, char *message)
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

    encodeMessage(bitmap, message);

    writeBitmap(out, bitmap);

    // CLEANUP
    freeBitmap(bitmap);
    fclose(in);
    fclose(out);
    return 0;
}

void encodeMessage(BMP *bitmap, char *message)
{
    int l = strlen(message);
    int c = 0;

    encodeChar(bitmap->pixels, 0, l);
    for (int i = 0; i < l; i++)
    {
        encodeChar(bitmap->pixels, (i + 1) * 8, message[i]);
    }
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