# Indicar cuál es el resultado del siguiente programa para n = 6

```c
void main () {
  int i = 0, j = 0, n ;
  scanf("%d", &n);
  for (i += 2; j < n; j++, i += 2)
    printf("%d %d | ", i, j++);
}
```

### Solución

2 0 | 4 2 | 6 4 |
