Una empresa de correo gestiona los paquetes existentes en su depósito a la espera de ser despachados mediante una lista simple de destinos, conteniendo cada nodo:

- País destion (cadena de 3, ordenado)
- CP Ciudad Destino (entero positivo, ordenado dentro de cada país)
- Sublista de paquetes
  - Código paquete (cadena de 6)
  - Volumen (en cms cubicos, entero positivo)

El código de paquete se compone por una letra y 6 números, la letra indica la categoría del paquete:

- [F]ragil
- [A]limento
- [N]ormal

Además, existe una cola, que contiene paquetes para ser ingresados al depósito. Cada elemento de la cola tiene los siguientes campos:

- País destino (cadena de 3)
- CP Ciudad Destino (entero positivo)
- Código paquete (cadena de 6, formato validado)
- Volumen (en cms cúbicos, entero positivo)

Se pide:

1. Definir, en tdacolac.h los tipos correspondientes al elemento de la cola y a la cola (implementación circular). Entregar como comentario en el .c de la resolución.
2. Cargar la lista de destinos (inicialmente sin paquetes) a partir de un archivo de texto o desde teclado. Cargar la cola de paquetes para ingresar.
3. Registrar el ingreso al depósito de los paquetes que tiene la cola, agregando el nuevo paquete al final de la sublista correspondiente. Aquellos paquetes con destino inexistente en la lista simple no se ingresan y deberán permanecer en la cola en el orden original. Como resumen del proceso, informar volumen ingresado por cada categoría de paquete y el porcentaje de paquetes no ingresados al depósito.
4. Consultar para un país destino P (dato ingresado por teclado, puede no existir) la cantidad de paquetes por ciudad y el volumen promedio de los mismos.
5. Escribir el main completo con las invocaciones a los subprogramas desarrollados.
