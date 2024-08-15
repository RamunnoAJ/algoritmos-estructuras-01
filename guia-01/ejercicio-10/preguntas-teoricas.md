## a) ¿Qué es y para qué se utiliza un ?. Especifique cuáles son las etapas por las que pasa un programa para convertirse en ejecutable.

Es el primer programa invocado por el compilador y procesa directivas como #include o #define.

Las etapas por las que pasa un programa para convertirse en ejecutable son:

1. Tokenizado léxico - El preprocesador reemplaza la secuencia de trigrafos por los caracteres que representan.
2. Empalmado de líneas - Las líneas de código que continúan con secuencias de escape de nueva línea son unidas para formar líneas lógicas.
3. Tokenización - Reemplaza los comentarios por espacios en blanco. Divide cada uno de los elementos a preprocesar por un carácter de separación.
4. Expansión de macros y gestión de directivas - Ejecuta las líneas con directivas de preprocesado incluyendo las que incluye otros archivos y las de compilación condicional.

## b) ¿El lenguaje C es case sensitive?

Si, el lenguaje C es case sensitive.

## c) ¿Qué diferencia existe entre un operador unario y uno binario?

Un operador unario afecta a una única variable o elemento y un operador binario afecta a dos variables o elementos.

## d) ¿Qué interpreta como valor verdadero y falso el lenguaje C?

C interpreta como veradedor al 1 y como falso al 0.

## e) ¿Cuáles son los formatos que se utilizan para los siguientes tipos? char, short, unsigned short, int, unsigned int, long, unsigned long, float, double.

char: %c
short: %hd
unsigned short: %hu
int: %d
unsigned int: %u
long: %ld
unsigned long: %lu
float: %f
double: %e

## f) ¿Por qué se dice que el conjunto de caracteres es incluido en el conjunto de los enteros?

Porque pueden ser representados por su posición en la tabla ASCII, que en efecto, son números enteros.

## g) ¿Cómo se utiliza y qué devuelve la función scanf, cuál es la ventaja que aporta este valor de retorno?

La función scanf sirve para ingresar datos por teclado, y se utiliza invocandola y pasandole 2 o más parámetros, el primero vendría a ser un string que tenga el formato del tipo correcto a la variable que queremos almacenar, y los próximos parámetros serían la dirección de las variables a quienes queremos darle el valor ingreado por teclado.
Está función devuelve el número de inputs correctamente matcheados y asignados, este número puede ser menor al número de variables proporcionadas o incluso cero. Y sirve para ciclar su uso.

## h) Analice las distintas posibilidades para leer caracteres.

Para leer caracteres podemos leerlos de a uno como caracter único de tipo char, como tipo int leyendo su correspondiente valor entero con respecto a la tabla ASCII, o como un arreglo de caracteres en caso de leer una cadena.
