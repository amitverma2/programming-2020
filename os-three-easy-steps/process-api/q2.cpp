#include<cstdio>
#include<cstdlib>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main() {
  int x;
  x = 100;

  int fd = open("q2.scratch", O_RDWR|O_CREAT, S_IRWXU|S_IRWXG|S_IRWXO);
  if (fd < 0) {
      printf("%d : Parent : File open failed (%d)\n", getpid(), fd);
      exit(1);
  }

  int rc = fork();

  if (rc < 0) {
    printf("%d : Parent : Fork failed (%d)\n", getpid(), rc);
    exit(1);
  } else if (rc == 0) {
    rc = wait(NULL);
    printf("%d : Child : Wait returned (%d)\n", getpid(), rc);
    // Child
    x = 20;
    printf("%d : Child : x is now %d\n", getpid(), x);

    char child[256];
    sprintf(child, "%d: Child : Hello,\n", getpid());
    ssize_t sz = write(fd, child , strlen(child));
    printf("%d : Child : Num chars written into file %ld\n", getpid(), sz);

    rc = execl("/bin/ls", "ls", "-al", 0);
    exit(0);
  } else {
    // Parent 
    x = 30;
    printf("%d : Parent : x is now %d\n", getpid(), x);

    char parent[256];
    sprintf(parent, "%d: Parent : World!\n", getpid());
    ssize_t sz = write(fd, parent , strlen(parent));
    printf("%d : Parent : Num chars written into file %ld\n", getpid(), sz);

    rc = wait(NULL);
    printf("%d : Parent : Wait returned (%d)\n", getpid(), rc);
    exit(0);
  }
  return 0;
}
