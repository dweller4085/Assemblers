#include <cstdint>
#include <cstdio>


unsigned w (unsigned v) {
    __asm popcnt eax, [v]
}

char * bin (uint8_t v, char buf [9]) {
    __asm {
        xor ecx, ecx
        mov edx, 7
        mov ebx, [buf]
        movzx eax, byte ptr [v]
        mov [ebx + 8], 0
L:      bt eax, edx
        jb B
        mov byte ptr [ebx + ecx], 48
        jmp E
B:      mov byte ptr [ebx + ecx], 49
E:      inc ecx
        dec edx
        cmp ecx, 8
        jnz L
        mov eax, ebx
    }
}


int main () {

    int is_popcnt_supported = 0;

    __asm {
        mov eax, 1
        cpuid
        bt ecx, 23
        jnb NOT_SET
        mov [is_popcnt_supported], 1
        NOT_SET:
    }

    printf ("Is popcnt supported on this CPU? : %d\n", is_popcnt_supported);


    char buf [9] = {0};

    uint8_t matrix [8] = {
        0b10110011,
        0b10000000,
        0b00101001,
        0b11111111,
        0b10111101,
        0b10100111,
        0b10100110,
        0b01100001
    };

    printf ("Original matrix:\n");
    for (unsigned i = 0; i < 8; i++)
        printf ("%d. %s : %d\n", i, bin (matrix[i], buf), w (matrix[i]));


    __asm {
        mov ecx, 1
        lea ebx, [matrix]
START:  mov edx, ecx
INSERT: cmp edx, 0
        jng ADVANCE
        movzx eax, byte ptr [ebx + edx - 1]
        popcnt eax, eax
        push eax
        movzx eax, byte ptr [ebx + edx]
        popcnt eax, eax
        cmp eax, [esp]
        pop eax
        jng ADVANCE
        mov al, [ebx + edx - 1]
        xchg al, [ebx + edx]
        xchg al, [ebx + edx - 1]
        dec edx
        jmp INSERT
ADVANCE:inc ecx
        cmp ecx, 8
        jnz START
    }


    printf ("\nMatrix with its rows sorted by weight:\n");
    for (unsigned i = 0; i < 8; i++)
        printf ("%d. %s : %d\n", i, bin (matrix[i], buf), w (matrix[i]));

    return 0;
}