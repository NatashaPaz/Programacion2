#include <stdio.h>
#include <stdlib.h>

void swap(int* i, int* j) {
    int aux;
    aux = *i;
    *i = *j;
    *j = aux;
    return;
}

void mostrar(int array[10], int i) {

    if (i < 10) {
        printf("%d, ", array[i]);
        mostrar(array, ++i);
    }

    return;
}


int main(void) {

    int i;
    int j;
    int n = 10;
    int array[10] = { 5,6,0,2,3,1,4,7,9,8 };

    printf("\narray desordenado:\n");
    mostrar(array, 0);

    i = 0;
    while (i < n) {
        j = 0;
        while (j < n) {
            //if (array[i] > array[j]) {    //asi ordena desc
            if (array[i] < array[j]) {      //asi ordena asc
                swap(&array[i], &array[j]);
            }

            j++;
        }
        i++;
    }
    printf("\narray ordenado:\n");
    mostrar(array, 0);
}

/*


void ordenar(nodo* actual)
{
     nodo *siguiente;
     nodo *aux=(nodo*)malloc(sizeof(nodo));

     while(actual->sig != NULL) //el actual ya empieza en cero y NULL ser�a el 10 (i<10)
     {
          siguiente = actual->sig;  //hace de j=0

          //busca el mas chico y lo swappea siempre al primer lugar, ascendiendo
          while(siguiente->sig !=NULL)  //(j<10)
          {
               if(actual->num > siguiente->num) //(o al reves)
               {
                    //swap
                    aux->num        =   siguiente->num;
                    siguiente->num  =   actual->num;
                    actual->num     =   aux->num;
               }
               siguiente = siguiente->sig;
          }
          //qued� el mas grande (o mas chico) y avanzamos un nodo
          actual = actual->sig;

     }//quedo ordenado y como solo swappeamos los contenidos la estructura qued� intacta. y no hace falta devolver nada
};


*/