# Analice cómo funciona la lectura en los siguientes programas, responda las preguntas que se formulan y describa un enunciado que justifique la solución que se implementa en cada uno de los siguientes programas:

## a)

```c
#include<stdio.h>
#define BLANCO ' '
int main (void) {
    char c;
    printf("Ingrese una cadena \n");
    while ((c = getchar()) != EOF)
        if(c == BLANCO)
            putchar(c);
        else
            putchar(c + 1);
    return 0;
}
```

### ¿Qué pasaría si se omiten los paréntesis en la expresión (c = getchar())?

El programa intentaría asignarle a "c" la variable "getchar" y como esta no existe el compilador nos daría un warning

### ¿Cuál es la ventaja de utilizar la constante EOF, el lugar de un punto o cualquier otro carácter estipulado?

Que nos aseguraríamos de que en el caso que el programa se encuentre con una linea de tipo End Of File, el while terminase, en cambio de la otra forma dependemos de un punto o cualquier otro carácter que un archivo pueda o no tener

## b)

```c
#include<stdio.h>
int main (void) {
    long sum = 0;
    int num, cont;
    cont = 0;
    printf("Ingrese numeros enteros y un * para terminar \n");
    while(scanf("%d", &num) == 1) {
     sum += num; cont++;
    }
    if(cont != 0)
        printf("el promedio es %0.2f", sum/(float)cont);
    else
        printf("NO hay numeros");
    return 0;
}
```

### ¿Cuándo se detiene el ciclo while?

El ciclo while se detiene cuando el usuario ingresa algo que no pueda ser interpretado como entero

### ¿Por qué se convierte a real la variable cont antes de dividir?

La variable cont se convierte a real antes de dividir para obtener un resultado de tipo real, necesitamos que uno de los dos valores que están siendo divididos sea de tipo float para obtener un resultado con comas.
