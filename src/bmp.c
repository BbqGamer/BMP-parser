#include "utils.h"
#include "histogram.h"

int main(int argc, char* argv[]) {
    if(argc == 2) {
        return histProgram(argv[1]);
    } else if (argc == 3) {
        printf("GRAYSCALE");
    } else if (argc == 4) {
        printf("ENCODE STEG");
    } else {
        printf("Wrong number of arguments");
    }

    return 0;
}