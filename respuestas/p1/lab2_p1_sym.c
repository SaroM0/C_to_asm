
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

// MOdificado por: Santiago Rodríguez Mora - 202110332
int esDigito (char num) {
    int rta;
    __asm {
        ; Load num into AL (byte) and check '0'..'9'
        mov     al, num
        cmp     al, '0'
        jl      not_digit
        cmp     al, '9'
        jg      not_digit

        ; rta = 1
        mov     eax, 1
        mov     rta, eax
        jmp     done

    not_digit:
        ; rta = 0
        xor     eax, eax
        mov     rta, eax

    done:
    }
    return rta;
}
