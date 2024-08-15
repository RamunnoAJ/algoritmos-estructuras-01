# Utilizando el operador condicional, reescriba las siguientes alternativas utilizando una sola sentencia:

## a)

```c
int a, b;
...........
if(a > 0)
    b = a;
else
    b = -a;
```

### Solución

```c
int a, b;
...........
b = a ? a > 0 : -a;
```

## b)

```c
int logica;
...........
if(logica)
    printf("verdadero");
else
    printf("falso");
```

### Solución

```c
int logica;
...........
printf("%s", logica ? "verdadero" : "falso");
```
