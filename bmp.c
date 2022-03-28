#include "utils.h"

int main() {
    //DOKOŃCZYC ARGV


    FILE *file = fopen("img/c-programming.bmp", "rb");
    LPBITMAPFILEHEADER header = readFileHeader(file);
    printFileHeader(header);

    LPBITMAPINFOHEADER infoHeader = readInfoHeader(file);
    printInfoHeader(infoHeader);

    HISTOGRAM h = histInit();
    freeHist(h);

    //CREATE HIST
    readFile(h, infoHeader, file);
    printHistogram(h, infoHeader->biWidth * infoHeader->biHeight);

    free(header);
    free(infoHeader);
    fclose(file);
    return 0;
}