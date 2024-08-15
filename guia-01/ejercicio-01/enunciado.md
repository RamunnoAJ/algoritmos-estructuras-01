# ¿Cuál es el valor almacenado en cada variable luego de ejecutado respectivo código?

## a)

```c
float x = 3.5, y = 4.7, z, w, q;
int verdadero, falso, n=0, nose;
w = (int)(x + y);
q = (int)x + (int)y;
verdadero = 10 > x;
falso = y < x;
nose = sizeof(int) == sizeof n;
z = x * (y = n++),
x = 'A' + n;
```

### Solución

x: 66.0
y: 0.00
z: 0.00
w: 8.00
q: 7.00
verdadero: 1
falso: 0
n: 1
nose: 1

## b)

```c
int resultado = 0, a = 3, b = 1, c;
resultado++;
resultado /= a;
resultado *= b;
c = resultado && a;
if (a == b)
 resultado = ++a;
else
 resultado = 'a';
a = b = resultado -- + c;
```

### Solución

resultado: 96
a: 97
b: 97
c: 0
