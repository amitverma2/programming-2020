#include<stdio.h>

int main(int argc, char *argv[])
{
    printf("Hello, world!\n");
    int a[3] = { [0...1]=3 };
    printf("%d %d %d\n", a[0], a[1], a[2]);
    return 0;
}