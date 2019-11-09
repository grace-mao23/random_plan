#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "randfile.h"

int rand_num() {
  int file = open("/dev/random", O_RDONLY);
  if (file == -1) {
    printf("errno: %s\n", strerror(errno));
  }
  int num = 0;
  int *buff = &num;
  int error_check = read(file, buff, 4);
  if (error_check == -1) {
    printf("errno: %s\n", strerror(errno));
  }
  return num;
}

int main() {
  //printf("Number: %d\n", rand_num());
  printf("Generating random numbers:\n");
  // 1. Populate array with 10 random numbers
  int numbers[10];
  int i = 0;
  for (; i < 10; i++) {
    numbers[i] = rand_num();
    printf("random %d: %d\n", i, numbers[i]);
  }

  printf("Writing numbers to file...\n");
  // 2. Write the array to a file
  int file = open("random", O_CREAT | O_RDWR, 0777);
  if (file == -1) {
    printf("errno: %s\n", strerror(errno));
  }
  int error = write(file, numbers, sizeof(int) * 10);
  if (error == -1) {
    printf("errno: %s\n", strerror(errno));
  }
  printf("Bytes written: %d\n", error);
  close(file);

  printf("Reading numbers from file...\n");
  // 3. Read file into a different array
  int new_nums[10];
  file = open("random", O_RDONLY);
  if (file == -1) {
    printf("errno: %s\n", strerror(errno));
  }
  error = read(file, new_nums, sizeof(int) * 10);
  if (error == -1) {
    printf("errno: %s\n", strerror(errno));
  }
  printf("Bytes read: %d\n", error);

  printf("Verification that written values were the same:\n");
  // 4. Print the contents of second array
  for (i = 0; i < 10; i++) {
    printf("random %d: %d\n", i, new_nums[i]);
  }
  close(file);
}
