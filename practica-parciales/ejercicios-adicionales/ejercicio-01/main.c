#include <stdio.h>
#include <string.h>
#define MAX_CODIGO 6
#define MAX_NOMBRE 31
#define MAX_DIMENSION 20

typedef struct {
  char codigo[MAX_CODIGO];
  int tiempo;
} Competicion;

typedef struct {
  char codigo[MAX_CODIGO];
  int tiempo;
  char nombre[MAX_NOMBRE];
} Record;

typedef struct {
  char nombre[MAX_NOMBRE];
  int competidores;
} Deporte;

void cargarCompeticiones();
void cargarRecords();
void generarRecords(Record records[], int *n);
void leer();
void procesarDatos(Record records[], int n);
int buscarCodigo(Record records[], int n, char codigo[MAX_CODIGO]);

int main() {
  Record records[MAX_DIMENSION];
  int n;
  cargarCompeticiones();
  cargarRecords();
  generarRecords(records, &n);
  // leer();

  procesarDatos(records, n);

  return 0;
}

void cargarCompeticiones() {
  FILE *ArchCompeticion, *ArchCompeticionB;
  Competicion c;

  ArchCompeticion = fopen("Competicion.txt", "rt");
  ArchCompeticionB = fopen("Competicion.dat", "wb");

  if (ArchCompeticion == NULL) {
    printf("No se pudo abrir el archivo Competicion.txt");
    return;
  }

  if (ArchCompeticionB == NULL) {
    printf("No se pudo abrir el archivo Competicion.dat");
    return;
  }

  while (fscanf(ArchCompeticion, "%s %d", c.codigo, &c.tiempo) == 2) {
    fflush(stdin);
    fwrite(&c, sizeof(Competicion), 1, ArchCompeticionB);
  }

  fclose(ArchCompeticion);
  fclose(ArchCompeticionB);
}

void cargarRecords() {
  FILE *ArchRecord, *ArchRecordB;
  Record r;

  ArchRecord = fopen("Records.txt", "rt");
  ArchRecordB = fopen("Records.dat", "wb");

  if (ArchRecord == NULL) {
    printf("No se pudo abrir el archivo Records.txt");
    return;
  }

  if (ArchRecordB == NULL) {
    printf("No se pudo abrir el archivo Records.dat");
    return;
  }

  fscanf(ArchRecord, "%s %s %d", r.codigo, r.nombre, &r.tiempo);
  while (!feof(ArchRecord)) {
    fwrite(&r, sizeof(Record), 1, ArchRecordB);
    fscanf(ArchRecord, "%s %s %d", r.codigo, r.nombre, &r.tiempo);
  }

  fclose(ArchRecord);
  fclose(ArchRecordB);
}

void generarRecords(Record records[], int *n) {
  FILE *Arch;
  Record r;

  Arch = fopen("Records.dat", "rb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Records.dat\n");
    return;
  }

  *n = 0;
  fread(&r, sizeof(Record), 1, Arch);
  while (!feof(Arch)) {
    records[*n] = r;
    (*n)++;
    fread(&r, sizeof(Record), 1, Arch);
  }

  fclose(Arch);
}

void leer() {
  FILE *ArchCompeticion, *ArchRecords;
  Competicion c;
  Record r;

  ArchCompeticion = fopen("Competicion.dat", "rb");
  ArchRecords = fopen("Records.dat", "rb");

  if (ArchCompeticion == NULL) {
    printf("No se pudo abrir el archivo Competicion.dat\n");
    return;
  }

  if (ArchRecords == NULL) {
    printf("No se pudo abrir el archivo Records.dat\n");
    return;
  }

  fread(&c, sizeof(Competicion), 1, ArchCompeticion);
  while (!feof(ArchCompeticion)) {
    printf("%s %d\n", c.codigo, c.tiempo);
    fread(&c, sizeof(Competicion), 1, ArchCompeticion);
  }

  fread(&r, sizeof(Record), 1, ArchRecords);
  while (!feof(ArchRecords)) {
    printf("%s %d %s\n", r.codigo, r.tiempo, r.nombre);
    fread(&r, sizeof(Record), 1, ArchRecords);
  }

  fclose(ArchCompeticion);
  fclose(ArchRecords);
}

void procesarDatos(Record records[], int n) {
  FILE *ArchCompeticion, *ArchRecords;
  Competicion c;
  Deporte deportes[MAX_DIMENSION];
  char codigo_actual[MAX_CODIGO], nombre_max_competidores[MAX_NOMBRE];
  int cant_competidores, max_competidores, i, cant_supero_record, suma_tiempo,
      m, suma_competidores;

  ArchCompeticion = fopen("Competicion.dat", "rb");
  ArchRecords = fopen("Records.dat", "rb");

  if (ArchCompeticion == NULL) {
    printf("No se pudo abrir el archivo Competicion.dat\n");
    return;
  }

  if (ArchRecords == NULL) {
    printf("No se pudo abrir el archivo Records.dat\n");
    return;
  }

  printf("Resultados de la competencia\n");
  printf("%-25s %-25s %-25s %-25s\n", "Deporte", "Cant. Competidores",
         "Cant. superó el record", "Tiempo promedio");

  max_competidores = 0;
  suma_competidores = 0;
  m = 0;
  fread(&c, sizeof(Competicion), 1, ArchCompeticion);
  while (!feof(ArchCompeticion)) {
    strcpy(codigo_actual, c.codigo);
    i = buscarCodigo(records, n, codigo_actual);

    printf("%-25s ", records[i].nombre);

    cant_competidores = 0;
    cant_supero_record = 0;
    suma_tiempo = 0;
    while (!feof(ArchCompeticion) && !strcmp(codigo_actual, c.codigo)) {
      cant_competidores++;
      if (c.tiempo < records[i].tiempo) {
        cant_supero_record++;
      }
      suma_tiempo += c.tiempo;

      fread(&c, sizeof(Competicion), 1, ArchCompeticion);
    }

    strcpy(deportes[m].nombre, records[i].nombre);
    deportes[m].competidores = cant_competidores;
    m++;
    suma_competidores += cant_competidores;

    if (cant_competidores > max_competidores) {
      max_competidores = cant_competidores;
      strcpy(nombre_max_competidores, records[i].nombre);
    }

    printf("%-25d %-25d %-25.2f\n", cant_competidores, cant_supero_record,
           (float)suma_tiempo / cant_competidores);
  }

  fclose(ArchCompeticion);
  fclose(ArchRecords);

  printf("Deporte con mayor cantidad de competidores: %s\n",
         nombre_max_competidores);

  printf("%-25s %-15s\n", "Deporte", "%");
  for (i = 0; i < m; i++) {
    printf("%-25s %-25.2f\n", deportes[i].nombre,
           deportes[i].competidores * 100 / (float)suma_competidores);
  }
}

int buscarCodigo(Record records[], int n, char codigo[MAX_CODIGO]) {
  int i = 0;

  while (i < n && strcmp(records[i].codigo, codigo)) {
    i++;
  }

  if (i < n) {
    return i;
  } else {
    return -1;
  }
}
