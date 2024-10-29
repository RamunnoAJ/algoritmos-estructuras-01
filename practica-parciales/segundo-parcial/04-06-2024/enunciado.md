Desarrollar un programa en lenguaje C, eficaz, eficiente, bien modularizado, robusto y claro, que resuelva el siguiente problema:

Una cadena de cafeterias con varias sucursales gestiona sus empleados mediante una lista simple de sucursales, donde cada nodo tiene:

- Codigo de sucursal (cadena de 4, ordenado)
- Cantidad de empleados activos
- Pila de empleados activos
  - Legajo (entero positivo)
  - Antigüedad (en años, entero positivo)

Además existe un archivo de texto (LICENCIAS.TXT) que en cada línea tiene, un pedido de licencia de un empleado:

- Código de sucursal (cadena de 4)
- Legajo del empleado (entero positivo)
- Motivo (caracter, [E]nfermedad, [F]ranco, [V]acaciones)

Se pide:

1. Definir, en tdapila.h los tipos correspondientes al elemento de la pila y a la pila (implementación estática). Entregar como comentario en el .c de la resolución.
2. Procesar los pedidos de licencia por vacaciones contenidas en el archivo de texto con el objetivo de eliminar de la pila al empleado correspondiente, si es que tiene un mínimo de 5 años de antigüedad; el resto de los empleados deberán permanecer en la misma manteniendo el orden en que se encontraban. Además, actualizar la cantidad de empleados activos de la sucursal. Cuando no exista la sucursal en la lista o no se encuentre el empleado en la sucursal correspondiente, el pedido será rechazado. Informar, al finalizar el proceso, la cantidad de pedidos rechazados y el porcentaje de eliminaciones concretadas sobre el total de los pedidos de vacaciones existentes en el archivo.
3. La cadena decide el cierre de las sucursales S1 y S2 (ingresadas por teclado y validadas, S1 menos a S2). Eliminarlas de la lista.
4. Escribir el main completo con las invocaciones a los subprogramas desarrollados, y los necesarios para la incialización y carga de las estructuras, los cuales no deben ser implementados.
