#include "utils.h"

int main(int argc, char* argv[]) {
    //DOKOŃCZYC ARGV

    FILE *file = fopen("img/c-programming.bmp", "rb");
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
    return 0;
}