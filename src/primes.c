#include "primes.h"

int isPrime(uint64_t p) {
  for (uint64_t i = 2; i <= sqrt(p); ++i) {
    if (p % i == 0)
      return 0;
  }
  return 1;
}

// Compute the prime factorisation of <n> and returns the number of factors
int getPrimeFactors(uint64_t n, uint64_t * destination) {
  //printf("Starting to factorize %llu\n", n);
  uint64_t numberOfFactors = 0;

  uint64_t i = 2;
  while (n > 1) {
    while (!isPrime(i))
      ++i;
    while (n % i == 0) {
      numberOfFactors++;
      destination[numberOfFactors-1] = i;
      n /= i;
    }
    if (n % i != 0)
      i++;
  }

  return numberOfFactors;
}