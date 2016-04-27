#include <time.h>


#ifdef SIMD

#define VERSION "simd"
#include "automata-simd.c"

#else

#define VERSION "naive"
#include "automata-naive.c"

#endif


double get_time() {
    struct timespec t;
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &t);
    return t.tv_sec + t.tv_nsec*1e-9;
}


void usage() {
    fprintf(stderr, "usage: automata <width> <ngens> <print>\n");
    fprintf(stderr, "version: %s\n", VERSION);
    exit(1);
}


int main(int argc, char **argv) {
    // the rule table, with 13 entries
    uint8_t rules[16] = {
        0, 3, 3, 4, 2, 3, 1, 2, 3, 3, 4, 3, 2
    };

    char syms[5] = {' ', '.', '*', 'o', 'O'};

    uint8_t *grid, *gen;

    int width = 512;
    int ngens = 2;
    int print;
    int i,j;

    if (argc != 4) usage();

    if (sscanf(argv[1], "%d", &width) != 1) usage();
    if (sscanf(argv[2], "%d", &ngens) != 1) usage();
    print = (argv[3][0] == 'y');


    if (width % 16) {
        fprintf(stderr, "width must be a multiple of 16!\n");
        exit(1);
    }

    grid = calloc(ngens * (width+2), sizeof(uint8_t));
    gen = grid + 1;
    for (i=0; i < width; i++) {
        gen[i] = rand() % 5;
    }

    double start = get_time();
    do_ca(grid, rules, width, ngens);
    double end = get_time();

    if (print) {
        for (i=0; i < ngens; i++) {
            gen = grid + i*(width+2)+1;
            for (j=0; j < width; j++) {
                printf("%1c", syms[gen[j]]);
            }
            printf("\n");
        }
    }

    printf("%lf\n", end-start);

    return 0;
}
