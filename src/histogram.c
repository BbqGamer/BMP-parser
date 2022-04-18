#include "histogram.h"

int histProgram(char* filename) {
    FILE *file = fopen(filename, "rb");
    
    if(file == NULL) {
        printf("File not found\n");
        return FILE_NOT_FOUND;
    }

    LPBITMAPFILEHEADER header = readFileHeader(file);
    printFileHeader(header);

    LPBITMAPINFOHEADER infoHeader = readInfoHeader(file);
    printInfoHeader(infoHeader);

    HISTOGRAM h = histInit();

    //CREATE HIST
    fillHist(h, infoHeader, file);
    printHistogram(h, infoHeader->biWidth * infoHeader->biHeight);

    freeHist(h);
    free(header);
    free(infoHeader);
    fclose(file);
}

HISTOGRAM histInit(void) {
    HISTOGRAM h = (HISTOGRAM)malloc(sizeof(COLOR)*NUM_COLORS);
    for(int i = 0; i < NUM_COLORS; i++) {
        h[i] = (COLOR)malloc(sizeof(int)*NUM_HIST_ROWS);
        for(int j = 0; j < NUM_HIST_ROWS; j++) {
            h[i][j] = 0;
        }
    } return h;
}

void freeHist(HISTOGRAM h) {
    for (int i = 0; i < NUM_COLORS; i++) {
        free(h[i]);
    } free(h);
}



void fillHist(HISTOGRAM h, LPBITMAPINFOHEADER infoHeader, FILE* file) {
    int lineSize = ((infoHeader->biBitCount * infoHeader->biWidth + 31)/32)*4;
    BYTE* buffer = (BYTE*)malloc(sizeof(BYTE)*lineSize);
    for(int i = 0; i < infoHeader->biHeight; i++) {
        fread(buffer, sizeof(BYTE), lineSize, file);
        BYTE pixel;
        for(int i = 0; i < infoHeader->biWidth; i++) {
            for(int j = 0; j < NUM_COLORS; j++) {
                pixel = buffer[3*i+j];
                h[j][pixel/16] += 1;
            }
        }
    }
    free(buffer);
}

void printHistogram(HISTOGRAM h, float numPixels) {
    for(int i = 0; i < NUM_COLORS; i++) {
        switch (i) { 
        case 0:
            printf("Blue\n");
            break;
        
        case 1:
            printf("Green\n");
            break;

        default:
            printf("Red\n");
            break;
        }
        for(int j = 0; j < NUM_HIST_ROWS; j++) {
            printf("  %d-%d: %.2f\%\n",j*STEP , j*STEP+STEP, h[i][j]/numPixels*100);
        }
        printf("\n");
    }
}
