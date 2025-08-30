
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

int esDigito (char num) {
    int rta;
    if (num>='0' && num<='9')
        rta = 1;
    else
        rta = 0;
    return rta;
}

