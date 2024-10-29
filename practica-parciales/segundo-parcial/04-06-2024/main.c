#include "tdapila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODIGO 5

typedef struct nodoL {
  char codigo_sucursal[MAX_CODIGO];
  int cant_empleados;
  TPILA empleados_activos;
  struct nodoL *sig;
} TNodo;

typedef TNodo *TLista;

void cargaLista(TLista *pl);
void procesaLista(TLista lista);
void eliminarEmpleado(TLista *pl, char codigo_sucursal[], int legajo,
                      int *pudoElim);
void eliminarNodoPorCodigo(TLista *pl, char c[]);

int main() {
  TLista lista, aux;
  FILE *arch;

  cargaLista(&lista);
  procesaLista(lista);

  return 0;
}

void procesaLista(TLista lista) {
  FILE *arch;
  TLista aux;
  TPILA paux;
  TELEMENTOP elem;
  char codigo_sucursal[MAX_CODIGO], motivo, s1[MAX_CODIGO], s2[MAX_CODIGO];
  int legajo, pedidos_vacaciones, pudoElim, pedidos_rechazados = 0,
                                            pedidos_concretados;

  arch = fopen("Licencias.txt", "rt");
  if (arch == NULL) {
    printf("No se pudo abrir el archivo Licencias.txt\n");
    return;
  } else {
    pedidos_concretados = 0;
    pedidos_vacaciones = 0;
    iniciap(&paux);

    while (fscanf(arch, "%s %d %c", codigo_sucursal, &legajo, &motivo) == 3) {
      if (motivo == 'V') {
        pedidos_vacaciones++;

        aux = lista;
        while (aux != NULL &&
               strcmp(aux->codigo_sucursal, codigo_sucursal) < 0) {
          aux = aux->sig;
        }

        if (aux != NULL && !strcmp(aux->codigo_sucursal, codigo_sucursal)) {
          eliminarEmpleado(&lista, codigo_sucursal, legajo, &pudoElim);
          if (!pudoElim) {
            pedidos_rechazados++;
          } else {
            pedidos_concretados++;
          }
        }
      }
    }

    printf("El total de pedidos rechazados es %d\n", pedidos_rechazados);
    if (pedidos_vacaciones > 0) {
      printf("El porcentaje de eliminaciones concretadas sobre el total de "
             "pedidos de vacaciones es %.2f %c",
             ((float)pedidos_concretados) * 100 / pedidos_vacaciones, '%');
    }

    printf("Ingresa dos sucursales que desee eliminar\n");
    scanf("%s %s", s1, s2);

    while (strcmp(s1, s2) >= 0) {
      printf("La primer sucursal debe ser menor a la segunda\n");
      scanf("%s %s", s1, s2);
    }

    eliminarNodoPorCodigo(&lista, s1);
    eliminarNodoPorCodigo(&lista, s2);
    fclose(arch);
  }
}

void eliminarEmpleado(TLista *pl, char codigo_sucursal[], int legajo,
                      int *pudoElim) {
  *pudoElim = 0;
  TLista aux = *pl, ant = NULL;
  TPILA paux;
  TELEMENTOP elem;
  iniciap(&paux);

  while (aux != NULL && strcmp(aux->codigo_sucursal, codigo_sucursal) < 0) {
    ant = aux;
    aux = aux->sig;
  }

  if (aux != NULL && !strcmp(aux->codigo_sucursal, codigo_sucursal)) {
    sacap(&aux->empleados_activos, &elem);
    ponep(&paux, elem);
    while (!vaciap(aux->empleados_activos) && elem.legajo < legajo) {
      sacap(&aux->empleados_activos, &elem);
      ponep(&paux, elem);
    }

    if (!vaciap(aux->empleados_activos) && elem.legajo == legajo &&
        elem.antiguedad >= 5) {
      sacap(&aux->empleados_activos, &elem);
      aux->cant_empleados--;
      *pudoElim = 1;
    }

    while (!vaciap(paux)) {
      sacap(&paux, &elem);
      ponep(&aux->empleados_activos, elem);
    }
  }
}

void eliminarNodoPorCodigo(TLista *pl, char c[]) {
  TLista aux, ant;
  TELEMENTOP elem;
  aux = *pl;
  ant = NULL;

  while (aux != NULL && strcmp(aux->codigo_sucursal, c) < 0) {
    ant = aux;
    aux = aux->sig;
  }

  if (aux != NULL && !strcmp(aux->codigo_sucursal, c)) {
    while (!vaciap(aux->empleados_activos)) {
      sacap(&aux->empleados_activos, &elem);
    }

    if (ant == NULL) {
      *pl = (*pl)->sig;
    } else {
      ant->sig = aux->sig;
    }

    free(aux);
  }
}
