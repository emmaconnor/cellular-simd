#include <stdint.h>
#include <stdio.h>
#include <x86intrin.h>

// width must be multiple of 16!!!
void do_ca(uint8_t *grid, uint8_t *rules, int width, int ngens) {
    int padded_width = width + 2;

    int geni, off, gen_end;
    uint8_t *gen;
    uint8_t *newgen;

    __m128i *new, *old, *end;
    __m128i table = *((__m128i*)rules);
    __m128i tmp;

    gen_end = ngens-1;
    gen = grid + 1;
    newgen = grid + padded_width + 1;
    for (geni=0; geni < gen_end; ++geni) {
        // pad left and right for continuous boundary conditions
        gen[-1] = gen[width-1];
        gen[width] = gen[0];

        // add neighborhoods
        end = (__m128i*)(newgen + width);
        for (off=-1; off <= 1; ++off) {
            old = (__m128i*)(gen + off);
            new = (__m128i*)(newgen);

            for (new = (__m128i*)(newgen); new < end; ++new) {
                _mm_storeu_si128(new, _mm_add_epi8(_mm_loadu_si128(old), _mm_loadu_si128(new)));
                ++old;
            }
        }

        // table lookups
        for (new = (__m128i*)(newgen); new < end; ++new) {
            _mm_storeu_si128(new,  _mm_shuffle_epi8(table, _mm_loadu_si128(new)));
        }

        gen += padded_width;
        newgen += padded_width;
    }
}


