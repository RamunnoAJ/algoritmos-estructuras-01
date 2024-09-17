#include <stdio.h>
#include <string.h>
#define MAX_DNI 9
#define MAX_CODIGO 5
#define MAX_DESCRIPCION 31
#define MAX_DIMENSION 50
#define DNI_CENTINELA "99999999"

typedef struct {
  char dni[MAX_DNI];
  char codigo_destino[MAX_CODIGO];
  int edad;
} Reserva;

typedef struct {
  char codigo[MAX_CODIGO];
  char descripcion[MAX_DESCRIPCION];
  float distancia;
} Destino;

void cargarReservas();
void cargarPresentes();
void cargarDestinos();
void generarDestinos(Destino destinos[], int *n);
void procesarDatos(Destino destinos[], int n);
int buscarDestino(Destino destinos[], int n, char codigo[]);
void listarViajeros();

int main() {
  int n;
  Destino destinos[50];

  cargarReservas();
  cargarPresentes();
  cargarDestinos();

  generarDestinos(destinos, &n);

  procesarDatos(destinos, n);
  listarViajeros();

  return 0;
}

void cargarReservas() {
  FILE *Arch, *ArchBinario;
  Reserva res;

  Arch = fopen("Reservas.txt", "rt");
  ArchBinario = fopen("Reservas.dat", "wb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Reservas.txt\n");
    return;
  }
  if (ArchBinario == NULL) {
    printf("No se pudo abrir el archivo Reservas.dat\n");
    return;
  }

  fscanf(Arch, "%s %s %d", res.dni, res.codigo_destino, &res.edad);
  while (!feof(Arch)) {
    fwrite(&res, sizeof(Reserva), 1, ArchBinario);
    fscanf(Arch, "%s %s %d", res.dni, res.codigo_destino, &res.edad);
  }

  fclose(Arch);
  fclose(ArchBinario);
}

void cargarPresentes() {
  FILE *Arch, *ArchBinario;
  Reserva pre;

  Arch = fopen("Presentes.txt", "rt");
  ArchBinario = fopen("Presentes.dat", "wb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Presentes.txt\n");
    return;
  }
  if (ArchBinario == NULL) {
    printf("No se pudo abrir el archivo Presentes.dat\n");
    return;
  }

  fscanf(Arch, "%s %s %d", pre.dni, pre.codigo_destino, &pre.edad);
  while (!feof(Arch)) {
    fwrite(&pre, sizeof(Reserva), 1, ArchBinario);
    fscanf(Arch, "%s %s %d", pre.dni, pre.codigo_destino, &pre.edad);
  }

  fclose(Arch);
  fclose(ArchBinario);
}

void cargarDestinos() {
  FILE *Arch, *ArchBinario;
  Destino des;

  Arch = fopen("Destinos.txt", "rt");
  ArchBinario = fopen("Destinos.dat", "wb");
  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Destinos.txt\n");
    return;
  }
  if (ArchBinario == NULL) {
    printf("No se pudo abrir el archivo Destinos.dat para escritura\n");
    return;
  }

  fscanf(Arch, "%s %s %f", des.codigo, des.descripcion, &des.distancia);
  while (!feof(Arch)) {
    fwrite(&des, sizeof(Destino), 1, ArchBinario);
    fscanf(Arch, "%s %s %f", des.codigo, des.descripcion, &des.distancia);
  }

  fclose(Arch);
  fclose(ArchBinario);
}

void generarDestinos(Destino destinos[], int *n) {
  FILE *Arch;
  Destino des;

  Arch = fopen("Destinos.dat", "rb");
  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Destinos.dat para lectura\n");
    return;
  }

  *n = 0;
  fread(&des, sizeof(Destino), 1, Arch);
  while (!feof(Arch)) {
    destinos[*n] = des;
    fread(&des, sizeof(Destino), 1, Arch);
    (*n)++;
  }

  fclose(Arch);
}

void procesarDatos(Destino destinos[], int n) {
  Reserva res, pre;
  FILE *ArchReservas, *ArchPresentes, *ArchViajeros;
  int cant_no_presentes, cant_sin_reserva, suma_edades, cant_viajeros, i;
  struct {
    char codigo_destino[MAX_CODIGO];
    char descripcion[MAX_DESCRIPCION];
    int cantidad;
  } viajeros_por_destino[MAX_DIMENSION];

  for (i = 0; i < n; i++) {
    strcpy(viajeros_por_destino[i].codigo_destino, destinos[i].codigo);
    strcpy(viajeros_por_destino[i].descripcion, destinos[i].descripcion);
    viajeros_por_destino[i].cantidad = 0;
  }

  ArchReservas = fopen("Reservas.dat", "rb");
  ArchPresentes = fopen("Presentes.dat", "rb");
  ArchViajeros = fopen("Viajeros.dat", "wb");

  if (ArchReservas == NULL) {
    printf("No se pudo abrir el archivo Reservas.dat\n");
    return;
  }
  if (ArchPresentes == NULL) {
    printf("No se pudo abrir el archivo Presentes.dat\n");
    return;
  }
  if (ArchViajeros == NULL) {
    printf("No se pudo abrir el archivo Viajeros.dat\n");
    return;
  }

  cant_no_presentes = 0;
  cant_sin_reserva = 0;
  suma_edades = 0;
  cant_viajeros = 0;

  fread(&res, sizeof(Reserva), 1, ArchReservas);
  fread(&pre, sizeof(Reserva), 1, ArchPresentes);
  while (!feof(ArchReservas) || !feof(ArchPresentes)) {
    if (strcmp(res.dni, pre.dni) < 0) {
      cant_no_presentes++;

      fread(&res, sizeof(Reserva), 1, ArchReservas);
    } else if (strcmp(res.dni, pre.dni) > 0) {
      cant_sin_reserva++;

      fread(&pre, sizeof(Reserva), 1, ArchPresentes);
    } else {
      if (strcmp(res.dni, DNI_CENTINELA) != 0) {
        cant_viajeros++;
        suma_edades += res.edad;
        i = buscarDestino(destinos, n, res.codigo_destino);
        if (i >= 0 && i < n) {
          viajeros_por_destino[i].cantidad++;
        } else {
          printf("El destino con código %s no existe\n", res.codigo_destino);
        }

        fwrite(&res, sizeof(Reserva), 1, ArchViajeros);
      }

      fread(&res, sizeof(Reserva), 1, ArchReservas);
      fread(&pre, sizeof(Reserva), 1, ArchPresentes);
    }
  }

  fclose(ArchReservas);
  fclose(ArchPresentes);
  fclose(ArchViajeros);

  printf("# Cantidad de pasajeros\n");
  printf("\tCon reserva que no se presentaron: %d\n", cant_no_presentes);
  printf("\tQue se presentaron sin reserva: %d\n", cant_sin_reserva);
  printf("# Edad promedio de los viajeros: %.2f\n",
         (float)suma_edades / cant_viajeros);
  printf("# Resumen de viajeros por destino\n");
  printf("\t%-25s %-25s\n", "Destino", "Cantidad");
  for (i = 0; i < n; i++) {
    printf("\t%-25s %-25d\n", viajeros_por_destino[i].descripcion,
           viajeros_por_destino[i].cantidad);
  }
}

int buscarDestino(Destino destinos[], int n, char codigo[]) {
  int i = 0;
  while (i < n && strcmp(destinos[i].codigo, codigo)) {
    i++;
  }

  if (i < n) {
    return i;
  } else {
    return -1;
  }
}

void listarViajeros() {
  FILE *Arch;
  Reserva via;

  Arch = fopen("Viajeros.dat", "rb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Viajeros.dat\n");
    return;
  }

  printf("# Viajeros.dat\n");
  fread(&via, sizeof(Reserva), 1, Arch);
  while (!feof(Arch)) {
    printf("%s %s %d\n", via.dni, via.codigo_destino, via.edad);
    fread(&via, sizeof(Reserva), 1, Arch);
  }

  fclose(Arch);
}
