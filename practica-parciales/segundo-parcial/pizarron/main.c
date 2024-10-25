#include "tdacolac.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodito {
  char codigo[7];
  unsigned int volumen;
  struct nodito *sig;
} TNodito;
typedef TNodito *TSublista;

typedef struct nodo {
  char pais[4];
  unsigned int ciudad;
  TSublista *sub;
  struct nodo *sig;
} TNodo;
typedef TNodo *TLista;

void cargador(TLista *pl, TCOLA *c);
void deposito(TLista l, TCOLA *c);
void insertarSublista(TSublista *sl, TELEMENTOC elem);

int main() {
  TLista l = NULL;
  TCOLA c;
  iniciac(&c);
  cargador(&l, &c);
  deposito(l, &c);

  return 0;
}

void cargador(TLista *pl, TCOLA *c) {
  TLista nuevo;
  TSublista nuevoSub;
  int cantP, i;
  FILE *arch;
  arch = fopen("datos.txt", "rt");

  if (arch != NULL) {
    nuevo = (TLista)malloc(sizeof(TNodo));
    while (fscanf(arch, "%s %d %d", nuevo->pais, &nuevo->ciudad, &cantP) == 3) {
      nuevo->sub = NULL;
      for (i = 0; i < cantP; i++) {
        nuevoSub = (TSublista)malloc(sizeof(TNodito));
        fscanf(arch, "%s %d", nuevoSub->codigo, &nuevoSub->volumen);
        nuevoSub->sig = *nuevo->sub;
        *nuevo->sub = nuevoSub;
      }
      nuevo->sig = *pl;
      *pl = nuevo;

      nuevo = (TLista)malloc(sizeof(TNodo));
    }
  }
}

void deposito(TLista l, TCOLA *c) {
  int totalP = 0, noIngresados = 0, acumVol[3] = {0}, i;
  char categorias[4] = {'F', 'A', 'N'};
  TLista aux;
  TELEMENTOC elem, centinela;
  strcpy(centinela.pais, "ZZZ");
  ponec(c, centinela);
  sacac(c, &elem);

  while (!vaciac(*c) && strcmp(elem.pais, centinela.pais)) {
    aux = l;
    totalP++;
    while (aux != NULL && strcmp(aux->pais, elem.pais) < 0) {
      aux = aux->sig;
    }
    while (aux != NULL && !strcmp(aux->pais, elem.pais) &&
           aux->ciudad < elem.ciudad) {
      aux = aux->sig;
    }
    if (aux != NULL && !strcmp(aux->pais, elem.pais) &&
        aux->ciudad == elem.ciudad) {
      insertarSublista(aux->sub, elem);
      i = 0;
      while (categorias[i] != elem.codigo[0]) {
        i++;
      }
      acumVol[i] += elem.volumen;
    } else {
      noIngresados++;
      ponec(c, elem);
    }

    sacac(c, &elem);
  }
}

void insertarSublista(TSublista *sl, TELEMENTOC elem) {
  TSublista nuevo, ant = NULL, act = *sl;
  nuevo = (TSublista)malloc(sizeof(TNodito));
  strcpy(nuevo->codigo, elem.codigo);
  nuevo->volumen = elem.volumen;
  nuevo->sig = NULL;

  while (act != NULL) {
    ant = act;
    act = act->sig;
  }

  if (ant == NULL) {
    *sl = nuevo;
  } else {
    ant->sig = nuevo;
  }
}
