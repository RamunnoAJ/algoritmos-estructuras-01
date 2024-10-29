#include "tdacolac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODIGO 7
#define MAX_PAIS 4

typedef struct nodito {
  char codigo[MAX_CODIGO];
  unsigned int volumen;
  struct nodito *sig;
} TNodito;

typedef TNodito *TSublista;

typedef struct nodo {
  char pais[MAX_PAIS];
  unsigned int ciudad;
  TSublista sl;
  struct nodo *sig;
} TNodo;

typedef TNodo *TLista;

void cargaLista(TLista *pl);
void deposito(TLista l, TCOLA *c);
void insertarSublista(TSublista *sl, TELEMENTOC elem);

int main() {
  TLista lista = NULL;
  TCOLA cola;

  iniciac(&cola);
  cargaLista(&lista);
  deposito(lista, &cola);

  return 0;
}

void cargaLista(TLista *pl) {
  TLista nuevo;
  TSublista nuevoSl;
  FILE *arch;
  int i, cantidad_paquetes;

  arch = fopen("Paquetes.txt", "rt");

  if (arch == NULL) {
    printf("No se pudo abrir el archivo Paquetes.txt\n");
  } else {
    while (!feof(arch)) {
      nuevo = (TLista)malloc(sizeof(TNodo));
      nuevo->sl = NULL;

      fscanf(arch, "%s %d %d", nuevo->pais, &nuevo->ciudad, &cantidad_paquetes);
      for (i = 0; i < cantidad_paquetes; i++) {
        nuevoSl = (TSublista)malloc(sizeof(TNodito));
        fscanf(arch, "%s %d", nuevoSl->codigo, &nuevoSl->volumen);
        nuevoSl->sig = nuevo->sl;
        nuevo->sl = nuevoSl;
      }

      nuevo->sig = *pl;
      *pl = nuevo;
    }
    fclose(arch);
  }
}

void deposito(TLista l, TCOLA *c) {
  int pedidos_totales = 0, no_ingresados = 0, acum_volumen[3] = {0};
  char categorias[4] = {'F', 'A', 'N'};
  TLista aux;
  TELEMENTOC elem, centinela;

  strcpy(centinela.pais, "ZZZ");
  ponec(c, centinela);

  sacac(c, &elem);
  while (!vaciac(*c) && strcmp(elem.pais, centinela.pais) != 0) {
    aux = l;
    pedidos_totales++;

    // Busca si el destino existe en la lista
    while (aux != NULL &&
           (strcmp(aux->pais, elem.pais) < 0 ||
            (strcmp(aux->pais, elem.pais) == 0 && aux->ciudad < elem.ciudad))) {
      aux = aux->sig;
    }

    if (aux != NULL && !strcmp(aux->pais, elem.pais) &&
        aux->ciudad == elem.ciudad) {
      insertarSublista(&(aux->sl), elem);
      int i = 0;
      while (categorias[i] != elem.codigo[0] && i < 3)
        i++;
      if (i < 3)
        acum_volumen[i] += elem.volumen;
    } else {
      no_ingresados++;
      ponec(c, elem);
    }

    sacac(c, &elem);
  }

  printf("Volumen ingresado por categoría:\n");
  printf("Fragil: %d\nAlimento: %d\nNormal: %d\n", acum_volumen[0],
         acum_volumen[1], acum_volumen[2]);
  printf("Porcentaje de paquetes no ingresados: %.2f%%\n",
         (no_ingresados * 100.0) / pedidos_totales);
}

void insertarSublista(TSublista *sl, TELEMENTOC elem) {
  TSublista nuevo = (TSublista)malloc(sizeof(TNodito));
  strcpy(nuevo->codigo, elem.codigo);
  nuevo->volumen = elem.volumen;
  nuevo->sig = NULL;

  if (*sl == NULL) {
    *sl = nuevo;
  } else {
    TSublista act = *sl;
    while (act->sig != NULL) {
      act = act->sig;
    }
    act->sig = nuevo;
  }
}

