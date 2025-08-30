
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
    int i;

    for (i=0; i<n && !centinela; i++) {
        int current_value = v[i];
        int result;
        __asm__ __volatile__ (
            "cmpl %2, %1\n\t"
            "sete %%al\n\t"
            "movzbl %%al, %0\n\t"
            : "=r" (result)
            : "r" (current_value), "r" (num)
            : "eax", "cc"
        );
        
        if (result) {
            centinela = 1;
        }
    }

    return centinela;
}
