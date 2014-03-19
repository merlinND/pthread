#include "sequential.h"

#include "primes.h"

static FILE * f;

void initSequentialContext(FILE * file) {
  f = file;
}

void runOneJob() {
  uint64_t number;
  int status = 0;
  while(status != -1) {
    status = fscanf(f, "%llu", &number);

    if (status != -1) {
      printPrimeFactors(number, NULL);
    }
  }
}
