#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "randfile.h"

int rand_num() {
  int file = open("/dev/random", O_RDONLY); // open the file
  if (file == -1) { // ERROR CHECK
    printf("errno: %s\n", strerror(errno));
  }
  int num = 0; // number to be returned
  int *buff = &num;
  int error_check = read(file, buff, 4); // reading in 4 bytes (an int)
  if (error_check == -1) { // ERROR CHECK
    printf("errno: %s\n", strerror(errno));
  }
  close(file); // close
  return num;
}

int main() {

  printf("Generating random numbers:\n");
  // 1. Populate array with 10 random numbers
  int numbers[10]; // array to be populated
  int i = 0;
  for (; i < 10; i++) {
    numbers[i] = rand_num(); // populate with 10 random numbers
    printf("random %d: %d\n", i, numbers[i]);
  }

  printf("\nWriting numbers to file...\n");
  // 2. Write the array to a file
  int file = open("random", O_CREAT | O_RDWR, 0777); // create random
  if (file == -1) { // ERROR CHECK
    printf("errno: %s\n", strerror(errno));
  }
  int error = write(file, numbers, sizeof(int) * 10); // write 10 ints
  if (error == -1) { // ERROR CHECK
    printf("errno: %s\n", strerror(errno));
  }
  printf("Bytes written: %d\n", error);
  close(file); // close

  printf("\nReading numbers from file...\n");
  // 3. Read file into a different array
  int new_nums[10]; // new array to be populated
  file = open("random", O_RDONLY);
  if (file == -1) { // ERROR CHECK
    printf("errno: %s\n", strerror(errno));
  }
  error = read(file, new_nums, sizeof(int) * 10); // read in 10 ints
  if (error == -1) { // ERROR CHECK
    printf("errno: %s\n", strerror(errno));
  }
  printf("Bytes read: %d\n", error);

  printf("\nVerification that written values were the same:\n");
  // 4. Print the contents of second array
  for (i = 0; i < 10; i++) {
    printf("random %d: %d\n", i, new_nums[i]);
  }

  close(file); // close

  return 0;
}
