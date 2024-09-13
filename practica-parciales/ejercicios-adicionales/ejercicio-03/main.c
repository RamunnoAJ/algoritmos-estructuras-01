#include <stdio.h>
#include <string.h>
#define MAX_CODIGO 5
#define MAX_APELLIDO 31
#define MAX_INASISTENCIA 30
#define CODIGO_CENTINELA "CC99"

typedef struct {
  char codigo[MAX_CODIGO];
  char apellido[MAX_APELLIDO];
  int inasistencias;
} Inscripto;

typedef struct {
  char codigo[MAX_CODIGO];
  char apellido[MAX_APELLIDO];
} Asistencia;

void cargarInscriptos();
void cargarAsistencia();
void procesarDatos(int clases);
void leerResultado();

int main() {
  int n;

  cargarInscriptos();
  cargarAsistencia();

  printf("Ingrese la cantidad de clases: ");
  scanf("%d", &n);
  procesarDatos(n);
  leerResultado();

  return 0;
}

void cargarInscriptos() {
  FILE *ArchInscriptos, *ArchInscriptosB;
  Inscripto inscripto;

  ArchInscriptos = fopen("Inscriptos.txt", "rt");
  ArchInscriptosB = fopen("Inscriptos.dat", "wb");

  if (ArchInscriptos == NULL) {
    printf("No se pudo abrir el archivo Inscriptos.txt");
    return;
  }
  if (ArchInscriptosB == NULL) {
    printf("No se pudo abrir el archivo Inscriptos.dat");
    return;
  }

  fscanf(ArchInscriptos, "%s %s %d", inscripto.codigo, inscripto.apellido,
         &inscripto.inasistencias);
  while (!feof(ArchInscriptos)) {
    fwrite(&inscripto, sizeof(Inscripto), 1, ArchInscriptosB);
    fscanf(ArchInscriptos, "%s %s %d", inscripto.codigo, inscripto.apellido,
           &inscripto.inasistencias);
  }

  strcpy(inscripto.codigo, CODIGO_CENTINELA);
  fwrite(&inscripto, sizeof(Inscripto), 1, ArchInscriptosB);

  fclose(ArchInscriptos);
  fclose(ArchInscriptosB);
}

void cargarAsistencia() {
  FILE *ArchAsistencia, *ArchAsistenciaB;
  Asistencia asistencia;

  ArchAsistencia = fopen("Asistencia.txt", "rt");
  ArchAsistenciaB = fopen("Asistencia.dat", "wb");

  if (ArchAsistencia == NULL) {
    printf("No se pudo abrir el archivo Asistencia.txt");
    return;
  }
  if (ArchAsistenciaB == NULL) {
    printf("No se pudo abrir el archivo Asistencia.dat");
    return;
  }

  fscanf(ArchAsistencia, "%s %s ", asistencia.codigo, asistencia.apellido);
  fwrite(&asistencia, sizeof(Asistencia), 1, ArchAsistenciaB);
  while (!feof(ArchAsistencia)) {
    fscanf(ArchAsistencia, "%s %s ", asistencia.codigo, asistencia.apellido);
    fwrite(&asistencia, sizeof(Asistencia), 1, ArchAsistenciaB);
  }

  strcpy(asistencia.codigo, CODIGO_CENTINELA);
  fwrite(&asistencia, sizeof(Asistencia), 1, ArchAsistenciaB);

  fclose(ArchAsistencia);
  fclose(ArchAsistenciaB);
}

void procesarDatos(int clases) {
  FILE *ArchInscriptos, *ArchAsistencia, *ArchInscriptosActualizado;
  Inscripto inscripto_actual;
  Asistencia asistencia_actual;
  int cant_inscriptos, n, i;
  char no_inscriptos[20][MAX_APELLIDO];

  ArchInscriptos = fopen("Inscriptos.dat", "rb");
  ArchAsistencia = fopen("Asistencia.dat", "rb");
  ArchInscriptosActualizado = fopen("InscriptosActualizado.dat", "wb");

  if (ArchInscriptos == NULL) {
    printf("No se pudo abrir el archivo Inscriptos.dat\n");
    return;
  }
  if (ArchAsistencia == NULL) {
    printf("No se pudo abrir el archivo Asistencia.dat\n");
    return;
  }
  if (ArchInscriptosActualizado == NULL) {
    printf("No se pudo abrir el archivo InscriptosActualizado.dat\n");
    return;
  }

  n = 0;
  cant_inscriptos = 0;

  fread(&inscripto_actual, sizeof(Inscripto), 1, ArchInscriptos);
  fread(&asistencia_actual, sizeof(Asistencia), 1, ArchAsistencia);
  while (!feof(ArchInscriptos) || !feof(ArchAsistencia)) {
    if (strcmp(inscripto_actual.codigo, asistencia_actual.codigo) < 0) {
      inscripto_actual.inasistencias++;
      if ((inscripto_actual.inasistencias * 100 / clases) < MAX_INASISTENCIA) {
        fwrite(&inscripto_actual, sizeof(Inscripto), 1,
               ArchInscriptosActualizado);
      }

      fread(&inscripto_actual, sizeof(Inscripto), 1, ArchInscriptos);
    } else if (strcmp(inscripto_actual.codigo, asistencia_actual.codigo) > 0) {
      strcpy(no_inscriptos[n], asistencia_actual.apellido);
      n++;

      fread(&asistencia_actual, sizeof(Asistencia), 1, ArchAsistencia);
    } else {
      if (strcmp(inscripto_actual.codigo, CODIGO_CENTINELA)) {
        cant_inscriptos++;
        if (!strcmp(inscripto_actual.apellido, asistencia_actual.apellido)) {
          fwrite(&inscripto_actual, sizeof(Inscripto), 1,
                 ArchInscriptosActualizado);
        } else {
          inscripto_actual.inasistencias++;
          if ((inscripto_actual.inasistencias * 100 / clases) <
              MAX_INASISTENCIA) {
            fwrite(&inscripto_actual, sizeof(Inscripto), 1,
                   ArchInscriptosActualizado);
          }
        }
      }

      fread(&inscripto_actual, sizeof(Inscripto), 1, ArchInscriptos);
      fread(&asistencia_actual, sizeof(Asistencia), 1, ArchAsistencia);
    }
  }

  fclose(ArchInscriptos);
  fclose(ArchAsistencia);
  fclose(ArchInscriptosActualizado);

  printf("Asistentes no inscriptos\n");
  for (i = 0; i < n; i++) {
    printf("%s\n", no_inscriptos[i]);
  }

  printf("Cantidad de asistentes inscriptos: %d\n", cant_inscriptos);
}

void leerResultado() {
  FILE *ArchResultado;
  Inscripto inscripto;

  ArchResultado = fopen("InscriptosActualizado.dat", "rb");

  if (ArchResultado == NULL) {
    printf("No se pudo abrir el archivo InscriptosActualizado.dat");
    return;
  }

  fread(&inscripto, sizeof(Inscripto), 1, ArchResultado);
  while (!feof(ArchResultado)) {
    printf("%s %s %d\n", inscripto.codigo, inscripto.apellido,
           inscripto.inasistencias);
    fread(&inscripto, sizeof(Inscripto), 1, ArchResultado);
  }

  fclose(ArchResultado);
}
