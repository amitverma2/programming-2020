#include<stdlib.h>
#include<stdio.h>

int main (void) {
  int* data = (int*)malloc(100 * sizeof(int));
  data[100] = 0;
  return 0;
}
