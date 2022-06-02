#include <iostream>
#include <cstdio>

#define n 6
#define m 5

using namespace std;

int main()
{
    setlocale(LC_ALL, "rus");

    char * format = "(%d, %d)\n";
    int specialElementCount = 0;
    int matrix[n*m] = 
    {
        3, 2, 2, 1, 1,
        3, 3, 3, 3, 1,
        1, 2, 3, 4, 5,
        5, 4, 3, 2, 1,
        1, 2, 1, 2, 1,
        5, 3, 3, 2, 2
    };

    cout << "Заданная матрица:" << endl;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << matrix [i*m + j] << " ";
        }
        cout << endl;
    }

    cout << "\nКоординаты особых точек (i, j):" << endl;

    __asm
    {
        mov ecx, n-1
ITROW:  mov edx, m-1
ITCOL:  mov esi, edx
        mov eax, m
        mul ecx
        add eax, esi
        lea ebx, [matrix + 4 * eax]
        mov edi, ebx
        mov eax, [ebx]
        mov edx, esi
CHECKL: sub ebx, 4
        dec edx
        jl NEXT
        cmp eax, [ebx]
        jge BAD
        jmp CHECKL
NEXT:   mov ebx, edi
        mov edx, esi
CHECKR: add ebx, 4
        inc edx
        cmp edx, m
        jz GOOD
        cmp eax, [ebx]
        jle BAD
        jmp CHECKR
GOOD:   inc [specialElementCount]
        push esi
        push ecx
        push dword ptr [format]
        call printf
        pop eax
        pop ecx
        pop edx
BAD:    mov edx, esi
        dec edx
        jge ITCOL
        dec ecx
        jge ITROW
    }

    cout << endl << "Количество особых элементов: " << specialElementCount << endl;
}
