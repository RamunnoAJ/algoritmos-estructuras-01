#include <stdio.h>
#include <string.h>
#define MAX_CODIGO 5
#define MAX_DIMENSION 20

typedef struct {
  char proyecto[MAX_CODIGO];
  int empleado;
  int semana;
  int horas;
} HorasSemanales;

typedef struct {
  char codigo[MAX_CODIGO];
  int horas_estimadas;
} Proyecto;

void cargarHorasSemanales();
void cargarProyectos(Proyecto proyectos[], int *n);
void procesarDatos(Proyecto proyectos[], int n);
int buscarProyecto(Proyecto proyectos[], int n, char codigo[MAX_CODIGO]);
float calcularDesvio(int horas_trabajadas, int horas_estimadas);

int main() {
  int n, i;
  Proyecto proyectos[MAX_DIMENSION];
  cargarHorasSemanales();
  cargarProyectos(proyectos, &n);

  procesarDatos(proyectos, n);

  return 0;
}

void cargarHorasSemanales() {
  FILE *Arch, *ArchBinario;
  HorasSemanales hs;

  Arch = fopen("HorasSemanales.txt", "rt");
  ArchBinario = fopen("HorasSemanales.dat", "wb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo HorasSemanales.txt\n");
    return;
  }
  if (ArchBinario == NULL) {
    printf("No se pudo abrir el archivo HorasSemanales.dat\n");
    return;
  }

  fscanf(Arch, "%s %d %d %d", hs.proyecto, &hs.empleado, &hs.semana, &hs.horas);
  fwrite(&hs, sizeof(HorasSemanales), 1, ArchBinario);
  while (!feof(Arch)) {
    fscanf(Arch, "%s %d %d %d", hs.proyecto, &hs.empleado, &hs.semana,
           &hs.horas);
    fwrite(&hs, sizeof(HorasSemanales), 1, ArchBinario);
  }

  fclose(Arch);
  fclose(ArchBinario);
}

void cargarProyectos(Proyecto proyectos[], int *n) {
  FILE *Arch, *ArchBinario;

  Arch = fopen("Proyectos.txt", "rt");
  ArchBinario = fopen("Proyectos.dat", "wb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Proyectos.txt\n");
    return;
  }
  if (ArchBinario == NULL) {
    printf("No se pudo abrir el archivo Proyectos.dat\n");
    return;
  }

  *n = 0;

  fscanf(Arch, "%s %d", proyectos[*n].codigo, &proyectos[*n].horas_estimadas);
  fwrite(&proyectos[*n], sizeof(Proyecto), 1, ArchBinario);
  while (!feof(Arch)) {
    (*n)++;
    fscanf(Arch, "%s %d", proyectos[*n].codigo, &proyectos[*n].horas_estimadas);
    fwrite(&proyectos[*n], sizeof(Proyecto), 1, ArchBinario);
  }

  fclose(Arch);
  fclose(ArchBinario);
}

void procesarDatos(Proyecto proyectos[], int n) {
  FILE *Arch;
  HorasSemanales horas_semanales;
  char hs_actual[MAX_CODIGO], proyecto_menor_desvio[MAX_CODIGO];
  int empleado_actual, horas_trabajadas, max_horas_trabajadas,
      empleado_max_horas, horas_proyecto_trabajadas, indice;
  float desvio, menor_desvio;

  Arch = fopen("HorasSemanales.dat", "rb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo HorasSemanales.dat\n");
    return;
  }

  menor_desvio = 9999;
  fread(&horas_semanales, sizeof(HorasSemanales), 1, Arch);
  while (!feof(Arch)) {
    strcpy(hs_actual, horas_semanales.proyecto);
    max_horas_trabajadas = 0;
    horas_proyecto_trabajadas = 0;

    printf("Proyecto: %s\n", horas_semanales.proyecto);
    printf("%-25s %-25s\n", "Empleado", "Horas trabajadas");
    while (!feof(Arch) && !strcmp(horas_semanales.proyecto, hs_actual)) {

      horas_trabajadas = 0;
      empleado_actual = horas_semanales.empleado;
      while (!feof(Arch) && !strcmp(horas_semanales.proyecto, hs_actual) &&
             empleado_actual == horas_semanales.empleado) {
        horas_trabajadas += horas_semanales.horas;

        fread(&horas_semanales, sizeof(HorasSemanales), 1, Arch);
      }
      printf("%-25d %-25d\n", empleado_actual, horas_trabajadas);

      if (horas_trabajadas > max_horas_trabajadas) {
        max_horas_trabajadas = horas_trabajadas;
        empleado_max_horas = empleado_actual;
      }
      horas_proyecto_trabajadas += horas_trabajadas;
    }

    indice = buscarProyecto(proyectos, n, hs_actual);
    desvio = calcularDesvio(horas_proyecto_trabajadas,
                            proyectos[indice].horas_estimadas);
    if (desvio < menor_desvio && desvio) {
      menor_desvio = desvio;
      strcpy(proyecto_menor_desvio, hs_actual);
    }

    printf("Empleado con más horas trabajadas en el proy: %d con %d hs\n",
           empleado_max_horas, max_horas_trabajadas);
    printf("Horas Proyecto %s: %d trabajadas. %d estimadas. Desvio: %.2f %c\n",
           hs_actual, horas_proyecto_trabajadas,
           proyectos[indice].horas_estimadas, desvio, '%');
  }

  printf("Proyecto con menor porcentaje de desvio: %s (%.2f%c)\n",
         proyecto_menor_desvio, menor_desvio, '%');

  fclose(Arch);
};

int buscarProyecto(Proyecto proyectos[], int n, char codigo[MAX_CODIGO]) {
  int i = 0;
  while (i < n && strcmp(codigo, proyectos[i].codigo)) {
    i++;
  }

  if (i < n) {
    return i;
  } else {
    return -1;
  }
}

float calcularDesvio(int horas_trabajadas, int horas_estimadas) {
  return ((float)horas_trabajadas - horas_estimadas) * 100 / horas_estimadas;
}
