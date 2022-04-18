#include "utils.h"
#include "histogram.h"
#include "grayscale.h"

int main(int argc, char* argv[]) {
    if(argc == 2) {
        return histProgram(argv[1]);
    } else if (argc == 3) {
        return grayscaleProgram(argv[1], argv[2]);
    } else if (argc == 4) {
        printf("ENCODE STEG");
    } else {
        printf("Wrong number of arguments");
    }

    return 0;
}