
#include <stdio.h>
#include <string.h>

int esDigito(char);

// Ejemplo usando inline assembly de Microsoft (dialect __asm)
int main() {

    char entrada[100];
    int tamReal;
    int i;
    int centinela;
    
    printf("Este programa determina si la cadena de entrada es numérica\n");
    printf("Escriba la cadena que quiere verificar: ");
    scanf("%s",entrada);
    tamReal = strlen(entrada);
    centinela = 1;
    for (i=0; i<tamReal && centinela; i++) {
        centinela = esDigito(entrada[i]);
    }
    if (centinela) {
        printf("la cadena es numérica \n");
    } else {
        printf("la cadena no es numérica \n");
    }
    return 0;
}

// Modificado por: Santiago Rodríguez Mora - 202110332
int esDigito (char num) {
    int rta;
    __asm {
        ; Stack assumptions:
        ;   [ebp+8]  = num (char)
        ;   [ebp-4]  = rta (int)

        mov     al, byte ptr [ebp+8]
        cmp     al, '0'
        jl      not_digit
        cmp     al, '9'
        jg      not_digit

        ; rta = 1
        mov     dword ptr [ebp-4], 1
        jmp     done

    not_digit:
        ; rta = 0
        mov     dword ptr [ebp-4], 0

    done:
    }
    return rta;
}
