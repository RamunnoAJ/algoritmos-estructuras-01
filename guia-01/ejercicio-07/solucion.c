#include <stdio.h>
int main() {
  for (int i = 0; i <= 9; i++) {
    for (int j = 0; j <= 9; j++) {
      for (int k = 0; k <= 9; k++) {
        printf("%d-%d-%d", i, j, k);
        printf(" ");
      }
    }
  }

  return 0;
}
