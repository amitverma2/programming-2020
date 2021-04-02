#include<cstdio>
#include<cstdlib>
#include<sys/types.h>
#include<unistd.h>

int main() {
  int x = 1;

  x = 100;

  int rc = fork();

  if (rc < 0) {
    printf("%d : Parent : Fork failed (%d)\n", getpid(), rc);
    exit(1);
  } else if (rc == 0) {
    // Parent
    x = 20;
    printf("%d : Parent : x is now %d\n", getpid(), x);
    wait(NULL);
    exit(0);
  } else {
    // Child
    x = 30;
    printf("%d : Child : x is now %d\n", getpid(), x);
    exit(0);
  }
  return 0;
}