#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <assert.h>
#include "vector.h"
#include "htables.h"

void test_get_bits_needed(){
    int16_t test[11] = {0, 1, -1, 2, -3, 4, -5, 25, 63, 64, 2047};
    uint32_t res[11] = {0, 1, 1, 2, 2, 3, 3, 5, 6, 7, 11};
    for (uint32_t i = 0; i < 11; i++)
    {
        assert(get_bits_needed(test[i]) == res[i]);
    }
}

void test_htable(){
    uint8_t val = htables_nb_symb_per_lengths[0][0][7];
    printf("%d\n", val);

}

int main(void)
{
    printf("test vector!\n");
    test_get_bits_needed();
    test_htable();
    return EXIT_SUCCESS;
}
