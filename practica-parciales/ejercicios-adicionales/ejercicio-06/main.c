#include <stdio.h>
#include <string.h>
#define MAX_DIM_CUPOS 3
#define MAX_DIM_CAPTURAS 2
#define MAX_CODIGO_ESPECIE 4
#define MAX_CODIGO_EMPRESA 5

typedef struct {
  char codigo[MAX_CODIGO_ESPECIE];
  float toneladas;
} Cupo;

typedef struct {
  char codigo_empresa[MAX_CODIGO_EMPRESA];
  Cupo cupos[MAX_DIM_CUPOS];
} Empresa;

typedef struct {
  char codigo_especie[MAX_CODIGO_ESPECIE];
  float toneladas;
} Captura;

typedef struct {
  char codigo_empresa[MAX_CODIGO_EMPRESA];
  char codigo_barco[MAX_CODIGO_ESPECIE];
  Captura capturas[MAX_DIM_CAPTURAS];
} Actividad;

typedef struct {
  char codigo_empresa[MAX_CODIGO_EMPRESA];
  char codigo_especie[MAX_CODIGO_ESPECIE];
  int cantidad;
} Multa;

void cargarCupos();
void cargarCapturas();
void procesarDatos();

int main() {
  cargarCupos();
  cargarCapturas();

  procesarDatos();

  return 0;
}

void cargarCupos() {
  FILE *Arch, *ArchBinario;
  int i;
  Empresa em;

  Arch = fopen("Cupos.txt", "rt");
  ArchBinario = fopen("Cupos.dat", "wb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Cupos.txt\n");
    return;
  }
  if (ArchBinario == NULL) {
    printf("No se pudo abrir el archivo Cupos.dat\n");
    return;
  }
  i = 0;

  fscanf(Arch, "%s", em.codigo_empresa);
  while (i < MAX_DIM_CUPOS) {
    fscanf(Arch, "%s %f", em.cupos[i].codigo, &em.cupos[i].toneladas);
  }

  while (!feof(Arch)) {
    fwrite(&em, sizeof(Empresa), 1, ArchBinario);
    fscanf(Arch, "%s", em.codigo_empresa);
    while (i < MAX_DIM_CUPOS) {
      fscanf(Arch, "%s %f", em.cupos[i].codigo, &em.cupos[i].toneladas);
    }
  }

  fclose(Arch);
  fclose(ArchBinario);
}

void cargarCapturas() {
  FILE *Arch, *ArchBinario;

  Arch = fopen("Capturas.txt", "rt");
  ArchBinario = fopen("Capturas.dat", "wb");

  fclose(Arch);
  fclose(ArchBinario);
}

void procesarDatos() {
  FILE *ArchCupos, *ArchCapturas, *ArchMultas;
  Empresa em;
  Actividad ac;

  ArchCupos = fopen("Cupos.dat", "rb");
  ArchCapturas = fopen("Capturas.dat", "rb");
  ArchMultas = fopen("Multas.dat", "wb");

  if (ArchCupos == NULL) {
    printf("No se pudo abrir el archivo Cupos.dat\n");
    return;
  }
  if (ArchCapturas == NULL) {
    printf("No se pudo abrir el archivo Capturas.dat\n");
    return;
  }
  if (ArchMultas == NULL) {
    printf("No se pudo abrir el archivo Multas.dat\n");
    return;
  }

  fread(&em, sizeof(Empresa), 1, ArchCupos);
  fread(&ac, sizeof(Actividad), 1, ArchCapturas);
  while (!feof(ArchCupos) || !feof(ArchCapturas)) {
    if (strcmp(em.codigo_empresa, ac.codigo_empresa) < 1) {

      fread(&em, sizeof(Empresa), 1, ArchCupos);
    } else if (strcmp(em.codigo_empresa, ac.codigo_empresa) > 1) {

      fread(&ac, sizeof(Actividad), 1, ArchCapturas);
    } else {

      fread(&em, sizeof(Empresa), 1, ArchCupos);
      fread(&ac, sizeof(Actividad), 1, ArchCapturas);
    }
  }
}
