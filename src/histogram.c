#include "histogram.h"

int histProgram(char *filename)
{
    FILE *file = fopen(filename, "rb");

    if (file == NULL)
    {
        printf("Error opening input file!\n");
        return FILE_NOT_FOUND;
    }

    // READ BITMAP
    BMP *bitmap = (BMP *)malloc(sizeof(BMP));
    readBitmap(file, bitmap);

    printHeaders(bitmap);

    // COUNT COLORS
    COLOR_COUNT *c = counterInit();
    fillCounter(c, bitmap, file);

    printHistogram(c, bitmap->infoHeader->biWidth * bitmap->infoHeader->biHeight);

    // CLEANUP
    freeCounter(c);
    freeBitmap(bitmap);
    fclose(file);
}

COLOR_COUNT *counterInit(void)
{
    COLOR_COUNT *c = (COLOR_COUNT *)malloc(sizeof(COLOR_COUNT));
    c->r = (int *)malloc(sizeof(int) * NUM_HIST_ROWS);
    c->g = (int *)malloc(sizeof(int) * NUM_HIST_ROWS);
    c->b = (int *)malloc(sizeof(int) * NUM_HIST_ROWS);
    for (int j = 0; j < NUM_HIST_ROWS; j++)
    {
        c->r[j] = 0;
        c->g[j] = 0;
        c->b[j] = 0;
    }
    return c;
}

void freeCounter(COLOR_COUNT *c)
{
    free(c->r);
    free(c->g);
    free(c->b);
    free(c);
}

void fillCounter(COLOR_COUNT *c, BMP *bitmap, FILE *file)
{
    BYTE *ptr = bitmap->pixels;
    for (int i = 0; i < bitmap->infoHeader->biWidth * bitmap->infoHeader->biHeight; i++)
    {
        PIXEL pixel;
        memcpy(&pixel, ptr, sizeof(PIXEL));
        ptr += sizeof(PIXEL);
        c->r[pixel.r / STEP]++;
        c->g[pixel.g / STEP]++;
        c->b[pixel.b / STEP]++;
    }
}

void printHistogram(COLOR_COUNT *c, float numPixels)
{
    for (int i = 0; i < NUM_COLORS; i++)
    {
        switch (i)
        {
        case 0:
            printf("Blue\n");
            for (int j = 0; j < NUM_HIST_ROWS; j++)
            {
                printf("  %d-%d: %.2f\%\n", j * STEP, j * STEP + STEP, (float)(c->b[j]) / numPixels * 100);
            }

            break;

        case 1:
            printf("Green\n");
            for (int j = 0; j < NUM_HIST_ROWS; j++)
            {
                printf("  %d-%d: %.2f\%\n", j * STEP, j * STEP + STEP, (float)(c->g[j]) / numPixels * 100);
            }
            break;

        default:
            printf("Red\n");
            for (int j = 0; j < NUM_HIST_ROWS; j++)
            {
                printf("  %d-%d: %.2f\%\n", j * STEP, j * STEP + STEP, (float)(c->r[j]) / numPixels * 100);
            }
            break;
        }
        printf("\n");
    }
}
