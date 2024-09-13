#include <stdio.h>
#include <string.h>
#define MAX_FECHA 7
#define MAX_HORARIO 6
#define LEGAJO_CENTINELA 99
#define FECHA_CENTINELA "999999"
#define HORARIO_CENTINELA "99:99"

typedef struct {
  char fecha[MAX_FECHA];
  int legajo;
  char horario_teorico[MAX_HORARIO];
  char horario_real[MAX_HORARIO];
  char estado;
} HoraEntPersonal;

typedef struct {
  char fecha[MAX_FECHA];
  int legajo;
  char hora[MAX_HORARIO];
} RelojEntrada;

void cargarHoraEntPersonal();
void cargarRelojEntrada();
void procesaArchivos();
void leeResultado();

int main() {
  cargarHoraEntPersonal();
  cargarRelojEntrada();

  procesaArchivos();

  return 0;
}

void cargarHoraEntPersonal() {
  FILE *ArchHoraEntPersonal, *ArchHoraEntPersonalB;
  HoraEntPersonal hep;

  ArchHoraEntPersonal = fopen("HoraEntPersonal.txt", "rt");
  ArchHoraEntPersonalB = fopen("HoraEntPersonal.dat", "wb");

  if (ArchHoraEntPersonal == NULL) {
    printf("No se pudo abrir el archivo HoraEntPersonal.txt");
    return;
  }
  if (ArchHoraEntPersonalB == NULL) {
    printf("No se pudo abrir el archivo HoraEntPersonal.dat");
    return;
  }

  fscanf(ArchHoraEntPersonal, "%s %d %s", hep.fecha, &hep.legajo,
         hep.horario_teorico);
  while (!feof(ArchHoraEntPersonal)) {
    fflush(stdin);
    fwrite(&hep, sizeof(HoraEntPersonal), 1, ArchHoraEntPersonalB);
    fscanf(ArchHoraEntPersonal, "%s %d %s", hep.fecha, &hep.legajo,
           hep.horario_teorico);
  }

  hep.legajo = LEGAJO_CENTINELA;
  strcpy(hep.fecha, FECHA_CENTINELA);
  strcpy(hep.horario_teorico, HORARIO_CENTINELA);
  fwrite(&hep, sizeof(HoraEntPersonal), 1, ArchHoraEntPersonalB);

  fclose(ArchHoraEntPersonal);
  fclose(ArchHoraEntPersonalB);
}

void cargarRelojEntrada() {
  FILE *ArchRelojEntrada, *ArchRelojEntradaB;
  RelojEntrada re;

  ArchRelojEntrada = fopen("RelojEntrada.txt", "rt");
  ArchRelojEntradaB = fopen("RelojEntrada.dat", "wb");

  if (ArchRelojEntrada == NULL) {
    printf("No se pudo abrir el archivo RelojEntrada.txt");
    return;
  }
  if (ArchRelojEntradaB == NULL) {
    printf("No se pudo abrir el archivo RelojEntrada.dat");
    return;
  }

  fscanf(ArchRelojEntrada, "%s %d %s", re.fecha, &re.legajo, re.hora);
  while (!feof(ArchRelojEntrada)) {
    fflush(stdin);
    fwrite(&re, sizeof(RelojEntrada), 1, ArchRelojEntradaB);
    fscanf(ArchRelojEntrada, "%s %d %s", re.fecha, &re.legajo, re.hora);
  }

  re.legajo = LEGAJO_CENTINELA;
  strcpy(re.fecha, FECHA_CENTINELA);
  strcpy(re.hora, HORARIO_CENTINELA);
  fwrite(&re, sizeof(HoraEntPersonal), 1, ArchRelojEntradaB);

  fclose(ArchRelojEntrada);
  fclose(ArchRelojEntradaB);
}

void procesaArchivos() {
  FILE *ArchHoraEntPersonal, *ArchRelojEntrada, *ArchHoraEntPersonalActualizado;
  HoraEntPersonal horario_actual;
  RelojEntrada reloj_actual;
  int cant_errores, cant_ausentes, n, cant_demoras;

  ArchHoraEntPersonal = fopen("HoraEntPersonal.dat", "rb");
  ArchRelojEntrada = fopen("RelojEntrada.dat", "rb");
  ArchHoraEntPersonalActualizado =
      fopen("HoraEntPersonalActualizado.dat", "wb");

  if (ArchHoraEntPersonal == NULL) {
    printf("No se pudo abrir el archivo HoraEntPersonal.dat\n");
    return;
  }
  if (ArchRelojEntrada == NULL) {
    printf("No se pudo abrir el archivo RelojEntrada.dat\n");
    return;
  }
  if (ArchHoraEntPersonalActualizado == NULL) {
    printf("No se pudo abrir el archivo HoraEntPersonalActualizado.dat\n");
    return;
  }

  cant_ausentes = 0;
  cant_demoras = 0;
  cant_errores = 0;
  n = 0;
  fread(&horario_actual, sizeof(HoraEntPersonal), 1, ArchHoraEntPersonal);
  fread(&reloj_actual, sizeof(RelojEntrada), 1, ArchRelojEntrada);
  while (!feof(ArchHoraEntPersonal) || !feof(ArchRelojEntrada)) {
    if (strcmp(horario_actual.fecha, reloj_actual.fecha) < 0) {
      horario_actual.estado = 'A';
      cant_ausentes++;
      fwrite(&horario_actual, sizeof(HoraEntPersonal), 1,
             ArchHoraEntPersonalActualizado);

      fread(&horario_actual, sizeof(HoraEntPersonal), 1, ArchHoraEntPersonal);
    } else if (strcmp(horario_actual.fecha, reloj_actual.fecha) > 0) {
      cant_errores++;
      fread(&reloj_actual, sizeof(RelojEntrada), 1, ArchRelojEntrada);
    } else {
      if (horario_actual.legajo < reloj_actual.legajo) {
        horario_actual.estado = 'A';
        cant_ausentes++;

        fwrite(&horario_actual, sizeof(HoraEntPersonal), 1,
               ArchHoraEntPersonalActualizado);
        fread(&horario_actual, sizeof(HoraEntPersonal), 1, ArchHoraEntPersonal);
      } else if (horario_actual.legajo > reloj_actual.legajo) {
        fread(&reloj_actual, sizeof(RelojEntrada), 1, ArchRelojEntrada);

      } else {
        strcpy(horario_actual.horario_real, reloj_actual.hora);
        if (strcmp(horario_actual.horario_teorico,
                   horario_actual.horario_real) < 0) {
          horario_actual.estado = 'T';
          cant_demoras++;
        } else {
          horario_actual.estado = 'P';
        }

        if (horario_actual.legajo != LEGAJO_CENTINELA) {
          fwrite(&horario_actual, sizeof(HoraEntPersonal), 1,
                 ArchHoraEntPersonalActualizado);
        }

        fread(&horario_actual, sizeof(HoraEntPersonal), 1, ArchHoraEntPersonal);
        fread(&reloj_actual, sizeof(RelojEntrada), 1, ArchRelojEntrada);
      }
      n++;
    }
  }

  fclose(ArchHoraEntPersonal);
  fclose(ArchRelojEntrada);
  fclose(ArchHoraEntPersonalActualizado);

  leeResultado();
  printf("%.2f %c de ausentismo. %d entradas demoradas\n",
         ((float)cant_ausentes * 100 / n), '%', cant_demoras);
  printf("%d fichada/s errónea/s\n", cant_errores);
}

void leeResultado() {
  FILE *ArchHoraEntPersonalActualizado;
  HoraEntPersonal hep;
  ArchHoraEntPersonalActualizado =
      fopen("HoraEntPersonalActualizado.dat", "rb");

  fread(&hep, sizeof(HoraEntPersonal), 1, ArchHoraEntPersonalActualizado);
  while (!feof(ArchHoraEntPersonalActualizado)) {
    printf("%s %d %s %s %c\n", hep.fecha, hep.legajo, hep.horario_teorico,
           hep.horario_real, hep.estado);

    fread(&hep, sizeof(HoraEntPersonal), 1, ArchHoraEntPersonalActualizado);
  }

  fclose(ArchHoraEntPersonalActualizado);
}
