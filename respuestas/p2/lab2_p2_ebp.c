
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int esta(int *, int, int);

// Ejemplo usando inline assembly de Microsoft (dialect __asm)
int main() {

    int tam=20;
    int * datos; 
    int buscado;
    int i,r;
    int rta;

    datos = calloc(tam,sizeof(int));
    srand(time(NULL));
    r = rand() % 20;
    printf("%d: \n",r);
    for (i=0; i<tam; i++) {
        datos[i] = i*(i+r);
    }

    printf("Este programa determina si un valor está en el vector (o no está)\n");
    printf("Escriba el valor que quiere buscar: ");
    scanf("%d",&buscado);
    rta = esta(datos, buscado, tam);
    
    if (rta) {
        printf("El valor %d está \n", buscado);
    } else {
        printf("El valor %d no está \n", buscado);
    }

    printf("Vector (para verificación):\n");
    for (int i=0; i<tam;i++) {
        printf("%d ",datos[i]);
    }
    printf("\n");

    return 0;
}

// función modificada por: Santiago Rodríguez Mora
int esta (int * v, int num, int n) {
    int centinela = 0;
    int i = 0;

    __asm__ __volatile__ (

        "movl $0, -4(%%ebp)\n\t"
        "movl $0, -8(%%ebp)\n\t"
        "0:\n\t"
        "movl -8(%%ebp), %%eax\n\t"
        "cmpl 16(%%ebp), %%eax\n\t"
        "jge 3f\n\t"
        "cmpl $0, -4(%%ebp)\n\t"
        "jne 3f\n\t"
        "movl 8(%%ebp), %%edx\n\t"
        "movl -8(%%ebp), %%ecx\n\t"
        "movl (%%edx,%%ecx,4), %%eax\n\t"
        "cmpl 12(%%ebp), %%eax\n\t"
        "jne 1f\n\t"
        "movl $1, -4(%%ebp)\n\t"
        "1:\n\t"
        "incl -8(%%ebp)\n\t"
        "jmp 0b\n\t"
        "3:\n\t"
        :
        :
        : "eax", "ecx", "edx", "cc", "memory"
    );

    return centinela;
}
