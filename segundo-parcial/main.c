#include "tdacolac.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX_NOMBRE 31

typedef struct nodito {
  unsigned int cantidad_pedida;
  unsigned int demora;
  struct nodito *sig;
} TNodito;

typedef TNodito *TSublista;

typedef struct nodo {
  unsigned int codigo;
  char nombre[MAX_NOMBRE];
  float precio;
  unsigned int cantidad_historicos;
  TSublista sl;
  struct nodo *sig;
} TNodo;

typedef TNodo *TLista;

void cargaLista(TLista *pl);
void cargaCola(TCOLAC *c);
void procesar(TLista pl, TCOLAC *c);
void insertarEnSublista(TSublista *sl, int cantP, int demora);
void imprimirImporteYDemora(
    TLista l); // Esto debía ir calculándose en tu función procesar(). No luego.
void eliminarItem(TLista *pl, unsigned int codigo);
void eliminarSublista(TSublista psl);

int main() {
  TLista lista;
  TCOLAC cola;
  unsigned int codigo;

  cargaLista(&lista);
  cargaCola(&cola);

  procesar(lista, &cola);
  imprimirImporteYDemora(lista);

  printf("Ingrese el codigo del item a eliminar\n");
  scanf("%d", &codigo);
  eliminarItem(&lista, codigo);

  return 0;
}

void procesar(TLista pl, TCOLAC *c) {
  TELEMENTOC celem, centinela;
  TLista aux;
  unsigned int demora;

  centinela.codigo = 999;
  ponec(c, centinela);

  sacac(c, &celem);
  while (celem.codigo != centinela.codigo) {
    aux = pl;
    if (celem.cant_pedida > 0) {
      while (aux != NULL && aux->codigo < celem.codigo) {
        aux = aux->sig;
      }

      if (aux != NULL && aux->codigo == celem.codigo) {
        aux->cantidad_historicos++;
        demora = celem.hora_entrega - celem.hora_pedido;
        insertarEnSublista(&aux->sl, celem.cant_pedida, demora);
      }

    } else {
      ponec(c, celem);
    }

    aux = pl;
    sacac(c, &celem);
  }
}

void insertarEnSublista(TSublista *sl, int cantP, int demora) {
  TSublista aux, nuevo, ant;

  ant = NULL;
  aux = *sl;

  nuevo = (TSublista)malloc(sizeof(TNodito));
  nuevo->cantidad_pedida = cantP;
  nuevo->demora = demora;
  nuevo->sig = NULL;

  while (aux != NULL) {
    ant = aux;
    aux = aux->sig;
  }

  if (aux == NULL) {
    *sl = nuevo;
  } else {
    ant->sig = nuevo;
  }
}

// Estos cálculos del importe y demora, debían hacerse a medida que procesaba
// los pedidos de la cola. Ya que solo había que tener en cuenta los nuevos
// pedidos procesados correctamente, y no todos los que había antes en la lista.
void imprimirImporteYDemora(TLista l) {
  TLista aux;
  TSublista slaux;
  int demora_suma;
  float demora_promedio;

  aux = l;

  while (aux != NULL) {
    printf("Lista codigo: %d, nombre: %s\n", aux->codigo, aux->nombre);
    demora_suma = 0;
    slaux = aux->sl;
    while (slaux != NULL) {
      demora_suma += slaux->demora;

      slaux = slaux->sig;
    }

    if (aux->cantidad_historicos != 0) {
      demora_promedio = ((float)demora_suma) / aux->cantidad_historicos;
      printf("Demora promedio: %.2f\n", demora_promedio);
    } else {
      printf("No se puede dividir por 0\n");
    }
    // Debía ser la cantidad que se pidió en cada pedido (SubLista), no la
    // cantidad total de pedidos del ítem (Lista).
    printf("El importe recaudado fue de: %.2f",
           aux->cantidad_historicos * aux->precio);
    aux = aux->sig;
  }
}

void eliminarItem(TLista *pl, unsigned int codigo) {
  TLista aux, ant;
  aux = *pl;
  ant = NULL;

  while (codigo != aux->codigo) {
    ant = aux;
    aux = aux->sig;
  }

  eliminarSublista(aux->sl);
  if (aux == *pl) {
    *pl = (*pl)->sig;
  } else {
    ant->sig = aux->sig;
  }

  free(aux);
  //  No calcula e informa la:
  //  - Cantidad promedio por pedido
  //  - Mayor demora de pedido
}

void eliminarSublista(TSublista psl) {
  TSublista aux, ant;
  aux = psl;
  ant = NULL;

  while (aux != NULL) {
    ant = aux;
    aux = aux->sig;
    free(ant);
  }
}

/* tdacolac.h
#define MAX 50

// Bien.
typedef struct {
    unsigned int codigo;
    unsgined int cant_pedida;
    unsigned int hora_pedido;
    unsigned int hora_entrega;
} TELEMENTOC;

// Bien.
typedef struct {
    TELEMENTOC items[MAX];
    int pri, ult;
} TCOLAC;

void iniciac(TCOLAC *c);
int vaciac(TCOLAC c);
int llena(TCOLAC c);
void ponec(TCOLAC *c, TELEMENTOC elem);
void sacac(TCOLAC *c, TELEMENTOC *elem);
void consultac(TCOLAC c, TELEMENTOC *elem);
 */
