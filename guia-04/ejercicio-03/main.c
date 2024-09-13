#include <stdio.h>
typedef struct {
  int numero_tarjeta;
  float importe;
  int cuotas;
} Gasto;

void cargarDatos();

int main() {
  int numero_tarjeta_actual;
  float tot_compras, importe_mayor;
  char financiacion;
  FILE *ArchGastos;
  Gasto g;
  cargarDatos();

  ArchGastos = fopen("Gastos.dat", "rb");
  if (ArchGastos == NULL) {
    printf("No se pudo abrir el archivo Gastos.dat");
    return 1;
  }
  printf("%-25s %-25s %-25s %-25s\n", "NRO. DE TARJETA", "TOTAL",
         "COMPRA DE MAYOR IMPORTE", "FINANCIACION (S/N)");

  fread(&g, sizeof(Gasto), 1, ArchGastos);
  while (!feof(ArchGastos)) {
    numero_tarjeta_actual = g.numero_tarjeta;
    tot_compras = 0, importe_mayor = 0;
    financiacion = 'N';
    printf("%-25d", g.numero_tarjeta);
    while (!feof(ArchGastos) && (g.numero_tarjeta == numero_tarjeta_actual)) {
      if (financiacion == 'N' && g.cuotas > 1) {
        financiacion = 'S';
      }

      if (g.importe > importe_mayor) {
        importe_mayor = g.importe;
      }
      tot_compras += g.importe;
      fread(&g, sizeof(Gasto), 1, ArchGastos);
    }

    printf(" %-25.2f %-25.2f %c\n", tot_compras, importe_mayor, financiacion);
  }

  return 0;
}

void cargarDatos() {
  Gasto g;
  FILE *ArchGTexto, *ArchGBinario;

  ArchGTexto = fopen("Gastos.txt", "rt");
  ArchGBinario = fopen("Gastos.dat", "wb");

  if (ArchGTexto == NULL) {
    printf("No se pudo abrir el archivo Gastos.txt\n");
    return;
  }
  if (ArchGBinario == NULL) {
    printf("No se pudo abrir el archivo Gastos.dat\n");
    return;
  }

  while (fscanf(ArchGTexto, "%d %f %d", &g.numero_tarjeta, &g.importe,
                &g.cuotas) == 3) {
    fwrite(&g, sizeof(Gasto), 1, ArchGBinario);
  }

  fclose(ArchGTexto);
  fclose(ArchGBinario);
}
