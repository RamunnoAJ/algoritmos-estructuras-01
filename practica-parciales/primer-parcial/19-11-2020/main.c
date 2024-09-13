#include <stdio.h>
#include <string.h>

#define MAX_DESCR 31
#define MAX_CODIGO 4
#define DIM_MAX 50

typedef struct {
  int codigo;
  char descripcion[MAX_DESCR];
  float porcentaje_comision;
} FormaPago;

typedef struct {
  char codigo[MAX_CODIGO];
  int forma_pago;
  float importe;
} CajaDiaria;

typedef struct {
  FormaPago forma_pago;
  float total;
} Total;

void cargarFormasPago();
void cargarCajaDiaria();
void leerFormasPago(FormaPago formasPago[], int *n);
void leerCajaDiaria(CajaDiaria cajasDiarias[], int *m);
int obtenerFormaPago(FormaPago formasPago[], int n, int codigo);
int obtenerTotal(Total totales[], int j, int codigo);
void procesaCajaDiaria(FormaPago formasPago[], int n, Total totales[], int j);

int main() {
  FormaPago formasPago[DIM_MAX];
  int n, i;
  char codigo_act[MAX_CODIGO];
  Total totales[DIM_MAX];

  cargarFormasPago();
  cargarCajaDiaria();
  leerFormasPago(formasPago, &n);

  for (i = 0; i < n; i++) {
    totales[i].forma_pago = formasPago[i];
    totales[i].total = 0;
  }

  procesaCajaDiaria(formasPago, n, totales, i);

  return 1;
}

void leerFormasPago(FormaPago formasPago[], int *n) {
  FILE *ArchFormasPago;
  *n = 0;

  ArchFormasPago = fopen("FormasPago.dat", "rb");
  if (ArchFormasPago == NULL) {
    printf("No se pudo leer el archivo de formas de pago.");
    return;
  }

  fread(&formasPago[*n], sizeof(FormaPago), 1, ArchFormasPago);
  while (!feof(ArchFormasPago)) {
    /*printf("%d %s %.2f\n", formasPago[*n].codigo,
     * formasPago[*n].descripcion,*/
    /*       formasPago[*n].porcentaje_comision);*/
    (*n)++;
    fread(&formasPago[*n], sizeof(FormaPago), 1, ArchFormasPago);
  }

  fclose(ArchFormasPago);
}

void cargarFormasPago() {
  FormaPago fp;
  FILE *ArchFPTexto, *ArchFPBinario;

  ArchFPTexto = fopen("FormasPago.txt", "rt");
  ArchFPBinario = fopen("FormasPago.dat", "wb");

  if (ArchFPTexto == NULL) {
    printf("No se pudo abrir el archivo FormasPago.txt\n");
    return;
  }
  if (ArchFPBinario == NULL) {
    printf("No se pudo abrir el archivo FormasPago.dat\n");
    return;
  }

  while (fscanf(ArchFPTexto, "%d %s %f", &fp.codigo, fp.descripcion,
                &fp.porcentaje_comision) == 3) {
    fflush(stdin);
    fwrite(&fp, sizeof(FormaPago), 1, ArchFPBinario);
  }

  fclose(ArchFPTexto);
  fclose(ArchFPBinario);
}

void cargarCajaDiaria() {
  CajaDiaria cd;
  FILE *ArchCDTexto, *ArchCDBinario;

  ArchCDTexto = fopen("CajaDiaria.txt", "rt");
  ArchCDBinario = fopen("CajaDiaria.dat", "wb");

  if (ArchCDTexto == NULL) {
    printf("No se pudo abrir el archivo CajaDiaria.txt\n");
    return;
  }
  if (ArchCDBinario == NULL) {
    printf("No se pudo abrir el archivo CajaDiaria.dat\n");
    return;
  }

  while (fscanf(ArchCDTexto, "%s %d %f", cd.codigo, &cd.forma_pago,
                &cd.importe) == 3) {
    fflush(stdin);
    fwrite(&cd, sizeof(CajaDiaria), 1, ArchCDBinario);
  }

  fclose(ArchCDTexto);
  fclose(ArchCDBinario);
}

void leerCajaDiaria(CajaDiaria cajasDiarias[], int *m) {
  FILE *ArchCajaDiaria;
  *m = 0;

  ArchCajaDiaria = fopen("CajaDiaria.dat", "rb");
  if (ArchCajaDiaria == NULL) {
    printf("No se pudo leer el archivo de caja diaria.");
    return;
  }

  fread(&cajasDiarias[*m], sizeof(CajaDiaria), 1, ArchCajaDiaria);
  while (!feof(ArchCajaDiaria)) {
    printf("%s %d %.2f\n", cajasDiarias[*m].codigo, cajasDiarias[*m].forma_pago,
           cajasDiarias[*m].importe);
    (*m)++;
    fread(&cajasDiarias[*m], sizeof(CajaDiaria), 1, ArchCajaDiaria);
  }

  fclose(ArchCajaDiaria);
}

int obtenerFormaPago(FormaPago formasPago[], int n, int codigo) {
  int i = 0;
  while (codigo != formasPago[i].codigo && i < n) {
    i++;
  }

  if (i < n) {
    return i;
  } else {
    return -1;
  }
}

int obtenerTotal(Total totales[], int j, int codigo) {
  int i = 0;
  while (codigo != totales[i].forma_pago.codigo && i < j) {
    i++;
  }

  if (i < j) {
    return i;
  } else {
    return -1;
  }
}

void procesaCajaDiaria(FormaPago formasPago[], int n, Total totales[], int j) {
  FILE *ArchCajaDiaria;
  CajaDiaria cd;
  FormaPago forma_pago_max_comisiones;
  int i, m, k, forma_pago_act, subtotal_ventas, tot_ventas, min_ventas;
  float tot_importe, tot_comisiones, max_comisiones, total = 0;
  char codigo_act[MAX_CODIGO], caja_min_ventas[MAX_CODIGO];

  ArchCajaDiaria = fopen("CajaDiaria.dat", "rb");
  if (ArchCajaDiaria == NULL) {
    printf("No se pudo leer el archivo de caja diaria.");
    return;
  }

  fread(&cd, sizeof(CajaDiaria), 1, ArchCajaDiaria);
  min_ventas = 10000;
  while (!feof(ArchCajaDiaria)) {
    printf("\nCaja %s \n", cd.codigo);
    printf("\t%-25s %-25s %-25s %-25s\n", "Forma Pago", "Cantidad Ventas",
           "Importe Total", "Importe Comisiones");
    strcpy(codigo_act, cd.codigo);

    max_comisiones = 0;
    tot_ventas = 0;

    while (!feof(ArchCajaDiaria) && !strcmp(codigo_act, cd.codigo)) {
      forma_pago_act = cd.forma_pago;
      subtotal_ventas = 0;
      tot_importe = 0;
      tot_comisiones = 0;

      while (!feof(ArchCajaDiaria) && !strcmp(codigo_act, cd.codigo) &&
             forma_pago_act == cd.forma_pago) {

        subtotal_ventas++;
        tot_importe += cd.importe;
        fread(&cd, sizeof(CajaDiaria), 1, ArchCajaDiaria);
      }

      tot_ventas += subtotal_ventas;
      i = obtenerFormaPago(formasPago, n, forma_pago_act);
      k = obtenerTotal(totales, j, formasPago[i].codigo);

      totales[k].total += tot_importe;
      total += tot_importe;

      tot_comisiones = tot_importe * formasPago[i].porcentaje_comision / 100;
      printf("\t%d-%-25s %-25d $ %-25.2f $ %-25.2f\n", cd.forma_pago,
             formasPago[i].descripcion, subtotal_ventas, tot_importe,
             tot_comisiones);

      if (tot_comisiones > max_comisiones) {
        forma_pago_max_comisiones = formasPago[i];
        max_comisiones = tot_comisiones;
      }
    }

    if (tot_ventas < min_ventas) {
      min_ventas = tot_ventas;
      strcpy(caja_min_ventas, codigo_act);
    }

    printf("\t\nForma de pago con mayor importe de comisiones: %s con $ %.2f\n",
           forma_pago_max_comisiones.descripcion, max_comisiones);
  }
  printf("\nCaja con menor cantidad de ventas: %s (%d)\n\n", caja_min_ventas,
         min_ventas);

  printf("Resumen ventas por Forma de Pago\n");
  printf("%-25s %-25s %-25s\n", "Forma de pago", "Importe", "Porcentaje");
  float suma_total = 0;
  for (i = 0; i < n; i++) {
    printf("%d-%-22s $ %-23.2f %.2f %s\n", totales[i].forma_pago.codigo,
           totales[i].forma_pago.descripcion, totales[i].total,
           totales[i].total * 100 / total, "%");
    suma_total += totales[i].total;
  }
  printf("%-25s $ %-23.2f %.2f %s\n", "TOTALES", suma_total, 100.0, "%");

  fclose(ArchCajaDiaria);
}
