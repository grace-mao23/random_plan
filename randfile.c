#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int rand_num() {
  int file = open("/dev/random", O_RDONLY);
  if (file == -1) {
    printf("errno: %s\n", strerror(errno));
  }
  int num = 0;
  int *buff = &num;
  int error_check = read(file, buff, 8);
  if (error_check == -1) {
    printf("errno: %s\n", strerror(errno));
  }
  return num;
}

int main() {
  printf("Number: %d\n", rand_num());
}
