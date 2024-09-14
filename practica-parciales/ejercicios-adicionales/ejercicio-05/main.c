#include <stdio.h>
#include <string.h>
#define MAX_FECHA 11
#define MAX_CODIGO 5

typedef struct {
  char fecha[MAX_FECHA];
  char deportista[MAX_CODIGO];
  float distancia;
} Tiro;

void cargarDeportistas();
void procesarDatos();

int main() {
  cargarDeportistas();
  procesarDatos();

  return 0;
}

void cargarDeportistas() {
  FILE *Arch, *ArchBinario;
  Tiro t;

  Arch = fopen("TiroAlBlanco.txt", "rt");
  ArchBinario = fopen("TiroAlBlanco.dat", "wb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo TiroAlBlanco.txt\n");
    return;
  }
  if (ArchBinario == NULL) {
    printf("No se pudo abrir el archivo TiroAlBlanco.dat\n");
    return;
  }

  fscanf(Arch, "%s %s %f", t.fecha, t.deportista, &t.distancia);
  while (!feof(Arch)) {
    fwrite(&t, sizeof(Tiro), 1, ArchBinario);
    fscanf(Arch, "%s %s %f", t.fecha, t.deportista, &t.distancia);
  }

  fclose(Arch);
  fclose(ArchBinario);
}

void procesarDatos() {
  FILE *Arch;
  Tiro t;
  char fecha_actual[MAX_FECHA], deportista_actual[MAX_CODIGO],
      deportista_min_promedio[MAX_CODIGO], fecha_menor_deportistas[MAX_FECHA];
  int cant_tiros, cant_deportistas, min_deportistas;
  float suma_tiros, min_tiro, min_promedio, promedio;

  Arch = fopen("TiroAlBlanco.dat", "rb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo TiroAlBlanco.dat\n");
    return;
  }

  min_deportistas = 999;
  fread(&t, sizeof(Tiro), 1, Arch);
  while (!feof(Arch)) {
    strcpy(fecha_actual, t.fecha);
    min_promedio = 999;
    cant_deportistas = 0;

    printf("Fecha %s\n", fecha_actual);
    printf("%-25s %-25s %-25s %-25s\n", "Codigo de Deportista",
           "Cantidad de Tiros", "Dist Promedio", "Dist Minima");
    while (!feof(Arch) && !strcmp(fecha_actual, t.fecha)) {
      strcpy(deportista_actual, t.deportista);
      cant_tiros = 0;
      suma_tiros = 0;
      min_tiro = 999;
      cant_deportistas++;

      while (!feof(Arch) && !strcmp(fecha_actual, t.fecha) &&
             !strcmp(deportista_actual, t.deportista)) {
        cant_tiros++;
        suma_tiros += t.distancia;

        if (t.distancia < min_tiro) {
          min_tiro = t.distancia;
        }

        fread(&t, sizeof(Tiro), 1, Arch);
      }

      promedio = suma_tiros / cant_tiros;
      printf("%-25s %-25d %-25.2f %-25.2f\n", deportista_actual, cant_tiros,
             promedio, min_tiro);
      if (promedio < min_promedio) {
        min_promedio = promedio;
        strcpy(deportista_min_promedio, deportista_actual);
      }
    }

    if (cant_deportistas < min_deportistas) {
      min_deportistas = cant_deportistas;
      strcpy(fecha_menor_deportistas, fecha_actual);
    }

    printf("Deportista con menor promedio: %s\n", deportista_min_promedio);
  }

  fclose(Arch);

  printf("Fecha con menos deportistas %s\n", fecha_menor_deportistas);
}
