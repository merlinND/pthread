#ifndef PRIMES_H
#define PRIMES_H

#include <stdint.h>
#include <pthread.h>

// ----- Constants
#define MAX_FACTORS 64
#define CACHE_SIZE 50

// ----- Structures
// Memoization
// TODO: replace by a hash map
struct cache_t {
  // The current number of numbers saved in the cache
  unsigned int size;
  // The actual numbers saved at each index
  uint64_t numbers[CACHE_SIZE];
  // The number of factors of the number at each index
  uint64_t numberOfFactors[CACHE_SIZE];
  // The prime factors of each of the numbers
  uint64_t factors[CACHE_SIZE][MAX_FACTORS];
};
typedef struct cache_t cache_t;

// ----- Functions
int isPrime(uint64_t p);

int getPrimeFactors(uint64_t n, uint64_t * destination);
int getMemoizedPrimeFactors(uint64_t n, cache_t * cache);

void printPrimeFactors(uint64_t n, pthread_mutex_t * outputMutex, cache_t * cache);

#endif
