#include<stdlib.h>
#include<stdio.h>

int main (void) {
  int* data = (int*)malloc(100 * sizeof(int));
  free(data + 2);
  return 0;
}
