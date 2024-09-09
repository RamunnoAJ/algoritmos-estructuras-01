#include <stdio.h>
#include <string.h>

typedef struct {
  char nombre[26];
  char seccion[6];
  char categoria[3];
} Empleado;

typedef struct {
  char codigo[11];
  char nombre[26];
} Seccion;

typedef struct {
  char codigo[3];
  float sueldo;
} Categoria;

void leer(Empleado empleados[], int *n, Seccion secciones[], int *m,
          Categoria categorias[], int *l);
void imprimirEmpleados(Empleado empleados[], int n);
void imprimirCategorias(Categoria categorias[], int l);
void imprimirSecciones(Seccion secciones[], int m);
void listadoSecciones(Seccion secciones[], int m, Empleado empleados[], int n);
int calcularCantidadSeccion(char codigo[6], Empleado empleados[], int n);
float calcularTotalSueldos(Empleado empleados[], int n, Categoria categorias[],
                           int l);

int main() {
  Empleado empleados[50];
  Seccion secciones[25];
  Categoria categorias[25];
  int n, m, l;

  leer(empleados, &n, secciones, &m, categorias, &l);
  listadoSecciones(secciones, m, empleados, n);

  printf("El total de sueldos de los empleados es: %.2f\n",
         calcularTotalSueldos(empleados, n, categorias, l));

  return 1;
}

void listadoSecciones(Seccion secciones[], int m, Empleado empleados[], int n) {
  int i;
  printf("%-25s %-20s \n", "Sección", "Cantidad empleados");
  printf("--------------------------------------------\n");

  for (i = 0; i < m; i++) {
    printf("%-25s %d\n", secciones[i].nombre,
           calcularCantidadSeccion(secciones[i].codigo, empleados, n));
  }
}

int calcularCantidadSeccion(char codigo[6], Empleado empleados[], int n) {
  int cantidad = 0, i;

  for (i = 0; i < n; i++) {
    if (strcmp(codigo, empleados[i].seccion) == 0) {
      cantidad++;
    }
  }

  return cantidad;
}

float calcularTotalSueldos(Empleado empleados[], int n, Categoria categorias[],
                           int l) {
  float total;
  int i, j;

  for (i = 0; i < n; i++) {
    j = 0;
    while (j < l && strcmp(empleados[i].categoria, categorias[j].codigo) != 0) {
      j++;
    }

    total += categorias[j].sueldo;
  }

  return total;
}

void leer(Empleado empleados[], int *n, Seccion secciones[], int *m,
          Categoria categorias[], int *l) {
  FILE *fpE, *fpS, *fpC;

  fpE = fopen("empleados.txt", "r");
  fpS = fopen("secciones.txt", "r");
  fpC = fopen("categorias.txt", "r");

  if (fpE == NULL) {
    printf("Error al abrir el archivo empleados.txt\n");
    return;
  }
  if (fpS == NULL) {
    printf("Error al abrir el archivo secciones.txt\n");
    return;
  }
  if (fpC == NULL) {
    printf("Error al abrir el archivo categorias.txt\n");
    return;
  }

  *n = 0;

  while (fscanf(fpE, "%s %s %s", empleados[*n].nombre, empleados[*n].seccion,
                empleados[*n].categoria) == 3) {
    (*n)++;
  }

  *m = 0;

  while (fscanf(fpS, "%s %s", secciones[*m].codigo, secciones[*m].nombre) ==
         2) {
    (*m)++;
  }

  *l = 0;

  while (fscanf(fpC, "%s %f", categorias[*l].codigo, &categorias[*l].sueldo) ==
         2) {
    (*l)++;
  }

  fclose(fpE);
  fclose(fpS);
  fclose(fpC);
}

void imprimirEmpleados(Empleado empleados[], int n) {
  int i;
  for (i = 0; i < n; i++) {
    printf("%s %s %s\n", empleados[i].nombre, empleados[i].categoria,
           empleados[i].seccion);
  }
}

void imprimirSecciones(Seccion secciones[], int m) {
  int i;
  for (i = 0; i < m; i++) {
    printf("%s %s\n", secciones[i].codigo, secciones[i].nombre);
  }
}

void imprimirCategorias(Categoria categorias[], int l) {
  int i;
  for (i = 0; i < l; i++) {
    printf("%s %.2f\n", categorias[i].codigo, categorias[i].sueldo);
  }
}
