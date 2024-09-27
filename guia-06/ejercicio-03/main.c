#include "tdapila.h"
#include <stdio.h>
#define MAX_CADENA 6

int main() {
  char cadena[MAX_CADENA], caracter;
  TPILA pila;
  int n, i;

  iniciap(&pila);
  scanf("%s", cadena);

  for (i = 0; i < MAX_CADENA - 1; i++) {
    ponep(&pila, cadena[i]);
    printf("cadena[%d]: %c\n", i, cadena[i]);
  }

  printf("Ingrese la cantidad de caracteres que quiere ver\n");
  scanf("%d", &n);
  while (!vaciap(pila) && n > 0) {
    if (n < MAX_CADENA) {
      sacap(&pila, &caracter);
      printf("%c\n", caracter);
    } else {
      printf("No flaquito, estás equivocadardo\n");
      break;
    }

    n--;
  }

  return 0;
}
