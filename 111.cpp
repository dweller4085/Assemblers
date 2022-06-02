#include <cstdio>

/*
    Rotate a square matrix quarterturn counterclockwise
*/

int main () {

    int const dim = 3;
    int matrix [dim * dim] = {
        9, 8, 7,
        6, 5, 4,
        3, 2, 1
    };

    printf ("Input matrix:\n");
    for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++)
        printf ("%d ", matrix[i*dim + j]);
        printf ("\n");
    }

    __asm {
        lea ebx, [matrix]
        xor esi, esi

TP:     lea edi, [esi + 1]
        cmp edi, [dim]
        jz TP_END

TP_COLS:mov eax, [dim]
        mul esi
        lea ecx, [eax + edi]
        
        mov eax, [dim]
        mul edi
        lea edx, [eax + esi]
        
        mov eax, [ebx + 4 * ecx]
        xchg eax, [ebx + 4 * edx]
        xchg eax, [ebx + 4 * ecx]
        
        inc edi
        cmp edi, [dim]
        jnz TP_COLS

        inc esi
        jmp TP

TP_END: mov eax, [dim]
        sar eax, 1
        push eax
        xor esi, esi

RV:     xor edi, edi
RV_COLS:mov eax, [dim]
        mul esi
        lea ecx, [eax + edi]
        mov eax, [dim]
        sub eax, esi
        dec eax
        mul [dim]
        lea edx, [eax + edi]

        mov eax, [ebx + 4 * ecx]
        xchg eax, [ebx + 4 * edx]
        xchg eax, [ebx + 4 * ecx]

        inc edi
        cmp edi, [dim]
        jnz RV_COLS

        inc esi
        cmp esi, [esp]
        jnz RV

        pop eax
    };

    printf ("\nRotated matrix:\n");
    for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++)
        printf ("%d ", matrix[i*dim + j]);
        printf ("\n");
    }

}
