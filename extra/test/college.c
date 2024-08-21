#include <stdio.h>

typedef struct Alumno {
  char matricula[10];
  char nombre[30];
  float promedio;
} Alumno;

void menu(int *op);
void leerDatos(Alumno alumnos[], int *n);
void imprimirDatos(Alumno alumnos[], int n);
int obtenerPosMaximoPromedio(Alumno alumnos[], int n);
void superanXPromedio(Alumno alumnos[], int n, Alumno superanPromedio[], int *m,
                      float x);

int main() {
  Alumno alumnos[20], superanPromedio[20];
  int n, m, posMaxPromedio, op;
  float x;

  leerDatos(alumnos, &n);
  do {
    menu(&op);
    switch (op) {
    case 1:
      imprimirDatos(alumnos, n);
      break;
    case 2:
      posMaxPromedio = obtenerPosMaximoPromedio(alumnos, n);
      printf("El alumno con mayor promedio es %s con un promedio de %.2f\n",
             alumnos[posMaxPromedio].nombre, alumnos[posMaxPromedio].promedio);
      break;
    case 3:
      printf("Ingrese un promedio X a superar: ");
      scanf("%f", &x);
      superanXPromedio(alumnos, n, superanPromedio, &m, x);
      imprimirDatos(superanPromedio, m);
      break;
    default:
      printf("Saliendo del programa...\n");
      break;
    }
  } while (op != 0);
}

void menu(int *op) {
  printf("\nMenú de opciones\n");
  printf("1) Listar los alumnos\n");
  printf("2) Obtener el alumno con mayor promedio\n");
  printf("3) Obtener los alumnos con promedio menor a X\n");
  printf("0) Salir\n\n");

  do {
    printf("Ingrese una de las opciones posibles: ");
    scanf("%d", op);
  } while (0 > *op || *op > 3);
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

int obtenerPosMaximoPromedio(Alumno alumnos[], int n) {
  int i = 0, posMaxPromedio;
  float maxPromedio = 0;
  while (i < n) {
    if (alumnos[i].promedio > maxPromedio) {
      posMaxPromedio = i;
      maxPromedio = alumnos[i].promedio;
    }
    i++;
  }

  return posMaxPromedio;
}

void superanXPromedio(Alumno alumnos[], int n, Alumno superanPromedio[], int *m,
                      float x) {
  int i;
  *m = 0;
  for (i = 0; i < n; i++) {
    if (alumnos[i].promedio > x) {
      superanPromedio[*m] = alumnos[i];
      (*m)++;
    }
  }
}
