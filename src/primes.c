#include <math.h>

#include "primes.h"

#define MAX_FACTORS 64

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


void printPrimeFactors(uint64_t n, pthread_mutex_t * outputMutex) {
  uint64_t factors[MAX_FACTORS];
  int numberOfFactors = getPrimeFactors(n, factors);

  // We use a mutex to guarantee that output will appear in order
  if(outputMutex != NULL) {
    pthread_mutex_lock(&outputMutex);
  }
  printf("%llu: ", n);
  for (int i = 0; i < numberOfFactors; ++i) {
    printf("%llu ", factors[i]);
  }
  printf("\n");
  if(outputMutex != NULL) {
    pthread_mutex_unlock(&outputMutex);
  }
}
