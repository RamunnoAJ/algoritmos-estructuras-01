#include <stdio.h>

typedef struct Alumno {
  char matricula[10];
  char nombre[30];
  float promedio;
} Alumno;

void leerDatos(Alumno alumnos[], int *n);
void imprimirDatos(Alumno alumnos[], int n);

int main() {
  Alumno alumnos[20];
  int n;
  leerDatos(alumnos, &n);
  imprimirDatos(alumnos, n);
}

void leerDatos(Alumno alumnos[], int *n) {
  FILE *fp;
  fp = fopen("alumnos.txt", "r");
  *n = 0;

  while (fscanf(fp, "%s %s %f", alumnos[*n].matricula, alumnos[*n].nombre,
                &alumnos[*n].promedio) == 3) {
    (*n)++;
  }
}

void imprimirDatos(Alumno alumnos[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("Matricula: %s\nNombre: %s\nPromedio: %.2f\n\n",
           alumnos[i].matricula, alumnos[i].nombre, alumnos[i].promedio);
  }
}
