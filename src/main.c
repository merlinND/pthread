#include <stdio.h>
#include <stdint.h>

int main() {
	printf("Hello world");

  FILE * f = fopen("numbers.txt", 'r');

  uint64_t number = 0;
  while(fscanf(f, "%d\n", &number)) {
    printPrimeFactors(number);
  }
}
