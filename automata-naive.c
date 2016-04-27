#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>


// width must be multiple of 32!!!
void do_ca(uint8_t *grid, uint8_t *rules, int width, int ngens) {
    int padded_width = width + 2;

    int geni, off, gen_end;
    uint8_t *gen;
    uint8_t *newgen;

    uint8_t *end, *new, *old;

    gen_end = ngens-1;
    gen = grid + 1;
    newgen = grid + padded_width + 1;
    for (geni=0; geni < gen_end; ++geni) {
        // pad left and right for continuous boundary conditions
        gen[-1] = gen[width-1];
        gen[width] = gen[0];

        // add neighborhoods
        end = (newgen + width);
        for (off=-1; off <= 1; ++off) {
            old = (gen + off);
            new = (newgen);

            for (new=newgen; new < end; ++new) {
                *new = *old + *new;
                ++old;
            }
        }

        // table lookups
        for (new=newgen; new < end; ++new) {
            *new = rules[*new];
        }

        gen += padded_width;
        newgen += padded_width;
    }
}


