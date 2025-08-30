
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

// función modificada por: Santiago Rodríguez Mora - 202110332
int esDigito (char num) {
    int rta;
    __asm__ __volatile__ (
        "movb 8(%%ebp), %%al\n\t"
        "cmpb $'0', %%al\n\t"
        "jl 1f\n\t"
        "cmpb $'9', %%al\n\t"
        "jg 1f\n\t"
        "movl $1, -4(%%ebp)\n\t"
        "jmp 2f\n"
        "1:\n\t"
        "movl $0, -4(%%ebp)\n"
        "2:\n\t"
        :
        :
        : "eax", "cc", "memory"
    );
    return rta;
}
