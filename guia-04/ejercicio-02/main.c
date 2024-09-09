#include <stdio.h>

typedef struct {
  char nombre[26];
  int edad;
  int codigo_deporte;
} Deportista;

typedef struct {
  int codigo;
  char descripcion[21];
} Deporte;

void cargarDat(Deportista deportistas[], Deporte deportes[]);
void leer(Deportista deportistas[], int *n, Deporte deportes[], int *m);

int main() {
  Deportista deportistas[50];
  Deporte deportes[20];
  int n, m;

  // cargarDat(deportistas, deportes);
  leer(deportistas, &n, deportes, &m);
  return 1;
}

void leer(Deportista deportistas[], int *n, Deporte deportes[], int *m) {
  FILE *fpb1, *fpb2;
  *n = 0;
  *m = 0;

  fpb1 = fopen("deportistas.dat", "rb");
  fpb2 = fopen("deportes.dat", "rb");

  fread(&deportistas[*n], sizeof(Deportista), 1, fpb1);
  while (!feof(fpb1)) {
    printf("%s %d %d\n", deportistas[*n].nombre, deportistas[*n].edad,
           deportistas[*n].codigo_deporte);

    (*n)++;
    fread(&deportistas[*n], sizeof(Deportista), 1, fpb1);
  }

  fread(&deportes[*m], sizeof(Deporte), 1, fpb2);
  while (!feof(fpb2)) {
    printf("%d %s \n", deportes[*m].codigo, deportes[*m].descripcion);

    (*m)++;
    fread(&deportes[*m], sizeof(Deporte), 1, fpb2);
  }

  fclose(fpb1);
  fclose(fpb2);
}

void cargarDat(Deportista deportistas[], Deporte deportes[]) {
  int n = 0, m = 0;
  FILE *fpt1, *fpt2, *fpb1, *fpb2;

  fpt1 = fopen("deportistas.txt", "rt");
  fpt2 = fopen("deportes.txt", "rt");
  fpb1 = fopen("deportistas.dat", "wb");
  fpb2 = fopen("deportes.dat", "wb");

  if (fpt1 == NULL) {
    printf("No se pudo abrir el archivo deportistas.txt\n");
    return;
  }
  if (fpt2 == NULL) {
    printf("No se pudo abrir el archivo deportes.txt\n");
    return;
  }
  if (fpb1 == NULL) {
    printf("No se pudo abrir el archivo deportistas.dat\n");
    return;
  }
  if (fpb2 == NULL) {
    printf("No se pudo abrir el archivo deportes.dat\n");
    return;
  }

  while (fscanf(fpt1, "%s %d %d", deportistas[n].nombre, &deportistas[n].edad,
                &deportistas[n].codigo_deporte) == 3) {
    fflush(stdin);
    fwrite(&deportistas[n], sizeof(Deportista), 1, fpb1);

    n++;
  }

  while (fscanf(fpt2, "%d %s", &deportes[m].codigo, deportes[m].descripcion) ==
         2) {
    fflush(stdin);
    fwrite(&deportes[m], sizeof(Deporte), 1, fpb2);

    n++;
  }

  fclose(fpt1);
  fclose(fpt2);
  fclose(fpb1);
  fclose(fpb2);
}
