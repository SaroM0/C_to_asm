
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

// Modificado por: Santiago Rodríguez Mora
int esta (int * v, int num, int n) {
    int centinela = 0;
    int i;

    __asm {
        ; centinela = 0; i = 0;
        mov     dword ptr [centinela], 0
        mov     dword ptr [i], 0

    for_loop:
        ; if (i >= n) break;
        mov     eax, [i]
        cmp     eax, [n]
        jge     end_for

        ; if (centinela != 0) break;
        cmp     dword ptr [centinela], 0
        jne     end_for

        ; if (v[i] == num) centinela = 1;
        mov     edx, [v]              ; base address
        mov     ecx, [i]              ; index
        mov     eax, [edx + ecx*4]    ; load v[i]
        cmp     eax, [num]
        jne     no_match
        mov     dword ptr [centinela], 1
    no_match:
        ; i++
        inc     dword ptr [i]
        jmp     for_loop

    end_for:
    }

    return centinela;
}
