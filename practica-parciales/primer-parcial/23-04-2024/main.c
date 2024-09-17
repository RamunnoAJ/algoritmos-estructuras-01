#include <stdio.h>
#include <string.h>
#define MAX_PERIODO 7
#define MAX_DESCRIPCION 31
#define MAX_DIMENSION 100

typedef struct {
  char periodo[MAX_PERIODO];
  int dia;
  int codigo_producto;
  int cantidad_gramos;
} Venta;

typedef struct {
  int codigo;
  char descripcion[MAX_DESCRIPCION];
  char rubro;
  float precio_kilo;
} Producto;

void cargarVentas();
void cargarProductos();
void procesarDatos(Producto productos[], int n);
void generarProductos(Producto productos[], int *n);
int buscarProducto(Producto productos[], int n, int codigo);

int main() {
  Producto productos[MAX_DIMENSION];
  int n;

  cargarVentas();
  cargarProductos();

  generarProductos(productos, &n);

  procesarDatos(productos, n);

  return 0;
}

void cargarVentas() {
  FILE *Arch, *ArchBinario;
  Venta v;

  Arch = fopen("Ventas.txt", "rt");
  ArchBinario = fopen("Ventas.dat", "wb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Ventas.txt\n");
    return;
  }
  if (ArchBinario == NULL) {
    printf("No se pudo abrir el archivo Ventas.dat\n");
    return;
  }

  fscanf(Arch, "%s %d %d %d", v.periodo, &v.dia, &v.codigo_producto,
         &v.cantidad_gramos);
  while (!feof(Arch)) {
    fwrite(&v, sizeof(Venta), 1, ArchBinario);
    fscanf(Arch, "%s %d %d %d", v.periodo, &v.dia, &v.codigo_producto,
           &v.cantidad_gramos);
  }

  fclose(Arch);
  fclose(ArchBinario);
}

void cargarProductos() {
  FILE *Arch, *ArchBinario;
  Producto p;

  Arch = fopen("Productos.txt", "rt");
  ArchBinario = fopen("Productos.dat", "wb");

  if (Arch == NULL) {
    printf("No se pudo abrir el archivo Productos.txt\n");
    return;
  }
  if (ArchBinario == NULL) {
    printf("No se pudo abrir el archivo Productos.dat\n");
    return;
  }

  fscanf(Arch, "%d %s %c %f", &p.codigo, p.descripcion, &p.rubro,
         &p.precio_kilo);
  while (!feof(Arch)) {
    fwrite(&p, sizeof(Producto), 1, ArchBinario);
    fscanf(Arch, "%d %s %c %f", &p.codigo, p.descripcion, &p.rubro,
           &p.precio_kilo);
  }

  fclose(Arch);
  fclose(ArchBinario);
}

void generarProductos(Producto productos[], int *n) {
  FILE *ArchProductos;
  Producto p;

  ArchProductos = fopen("Productos.dat", "rb");

  if (ArchProductos == NULL) {
    printf("No se pudo abrir el archivo Productos.dat para lectura\n");
    return;
  }

  *n = 0;
  fread(&p, sizeof(Producto), 1, ArchProductos);
  while (!feof(ArchProductos)) {
    productos[*n] = p;
    (*n)++;
    fread(&p, sizeof(Producto), 1, ArchProductos);
  }

  fclose(ArchProductos);
}

void procesarDatos(Producto productos[], int n) {
  FILE *ArchVentas;
  Venta v;
  char periodo_actual[MAX_PERIODO], rubro_mas_vendido;
  int codigo_actual, venta_mayor_cantidad, dia_venta_mayor_cantidad, indice,
      producto_menor_venta_total, cantidad_periodos;
  float total_vendido, menor_venta_total, venta_total_periodo,
      suma_total_ventas;

  ArchVentas = fopen("Ventas.dat", "rb");

  if (ArchVentas == NULL) {
    printf("No se pudo abrir el archivo Ventas.dat para lectura\n");
    return;
  }

  suma_total_ventas = 0;
  cantidad_periodos = 0;

  fread(&v, sizeof(Venta), 1, ArchVentas);
  while (!feof(ArchVentas)) {
    menor_venta_total = 99999.99;
    venta_total_periodo = 0;
    cantidad_periodos++;

    strcpy(periodo_actual, v.periodo);
    printf("# Periodo: %s\n", periodo_actual);
    printf("%-25s %-25s %-25s\n", "Desc. Producto", "Total vendido",
           "Venta mayor cantidad");
    while (!feof(ArchVentas) && !strcmp(periodo_actual, v.periodo)) {
      codigo_actual = v.codigo_producto;
      venta_mayor_cantidad = 0;
      dia_venta_mayor_cantidad = 0;
      total_vendido = 0;

      indice = buscarProducto(productos, n, codigo_actual);

      while (!feof(ArchVentas) && !strcmp(periodo_actual, v.periodo) &&
             codigo_actual == v.codigo_producto) {
        if (v.cantidad_gramos > venta_mayor_cantidad) {
          venta_mayor_cantidad = v.cantidad_gramos;
          dia_venta_mayor_cantidad = v.dia;
        }

        total_vendido +=
            v.cantidad_gramos / (float)1000 * productos[indice].precio_kilo;

        fread(&v, sizeof(Venta), 1, ArchVentas);
      }

      if (total_vendido <= menor_venta_total) {
        producto_menor_venta_total = codigo_actual;
        menor_venta_total = total_vendido;
      }

      printf("%-25s $ %-23.2f %-5d (Dia: %d)\n", productos[indice].descripcion,
             total_vendido, venta_mayor_cantidad, dia_venta_mayor_cantidad);

      venta_total_periodo += total_vendido;
    }

    suma_total_ventas += venta_total_periodo;
    printf("Producto con menor venta total: %s ($ %.2f)\n",
           productos[buscarProducto(productos, n, producto_menor_venta_total)]
               .descripcion,
           menor_venta_total);
    printf("Rubro más vendido: ($ )\n");
  }

  fclose(ArchVentas);
  printf("Valor promedio por periodo: $ %.2f\n",
         suma_total_ventas / cantidad_periodos);

  printf("# Resumen de ventas totales por producto\n");
}

int buscarProducto(Producto productos[], int n, int codigo) {
  int i = 0;
  while (i < n && productos[i].codigo != codigo) {
    i++;
  }

  return i;
}
