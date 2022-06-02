#include <cstdio>

/*
    Count the number of set bits on the antidiagonal of a square boolean matrix
*/

int main () {

    int const dim = 6;
    int bit_count = 0;
    int matrix [dim * dim] = {
        1, 1, 1, 1, 1, 0,
        0, 1, 1, 0, 1, 0,
        0, 1, 1, 0, 1, 0,
        1, 1, 1, 1, 1, 1,
        0, 1, 0, 1, 0, 1,
        0, 0, 0, 0, 0, 0
    };

    printf ("Input matrix:\n");
    for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++)
        printf ("%d ", matrix[i*dim + j]);
        printf ("\n");
    }

    __asm {
        mov ecx, [dim]
        mov eax, ecx
        dec eax
        mul ecx
        mov edx, eax
        dec ecx
        mov esi, ecx
        xor eax, eax
START:  add eax, [matrix + 4 * ecx]
        add ecx, esi
        cmp ecx, edx
        jng START
        mov [bit_count], eax
    };

    printf ("\nNumber of set bits on the antidiagonal: %d\n\n", bit_count);

}
