#include <math.h>
#include <stdio.h>

#include "primes.h"

/**
 * Try to find the given number in cache.
 * @return The index if found, -1 otherwise
 */
int findInCache(uint64_t n, cache_t * c) {
  for (int i = 0; i < c->size; ++i) {
    if (c->numbers[i] == n)
      return i;
  }
  return -1;
}

int isPrime(uint64_t p) {
  for (uint64_t i = 2; i <= sqrt(p); ++i) {
    if (p % i == 0)
      return 0;
  }
  return 1;
}

// Compute the prime factorisation of <n> and returns the number of factors
// TODO: look for more efficient algorithms?
int getPrimeFactors(uint64_t n, uint64_t * destination) {
  uint64_t numberOfFactors = 0;

  uint64_t i = 2;
  while (n > 1) {
    // TODO: cache prime numbers (in a thread-local prime-only cache)
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

/* Compute the prime factors of <n>, only if the solution is not already present in <cache>.
 * If the cache is not full, save the factors in the next available spot of the cache.
 * @return The number of prime factors of <n>, or -1 if the cache is full and thus `n` cannot be memoized
 */
int getMemoizedPrimeFactors(uint64_t n, cache_t * c) {
  // Check if the number is already present in cache
  int index = findInCache(n, c);
  if (index >= 0) {
    return c->numberOfFactors[index];
  }
  else if (c->size >= CACHE_SIZE) {
    return -1;
  }
  else {
    index = c->size;
    c->numberOfFactors[index] = getPrimeFactors(n, c->factors[index]);
    c->numbers[index] = n;
    c->size++;
    return c->numberOfFactors[index];
  }
}

/*
 * @param outputMutex Pass in NULL to ignore
 * @param cache Pass in NULL to ignore
 */
void printPrimeFactors(uint64_t n, pthread_mutex_t * outputMutex, cache_t * cache) {
  int numberOfFactors = -1;
  uint64_t * result;
  uint64_t factors[MAX_FACTORS];

  if (cache != NULL) {
    numberOfFactors = getMemoizedPrimeFactors(n, cache);
  }
  // The cache could be full and refuse to compute the factors
  if (numberOfFactors >= 0) {
    unsigned int index = findInCache(n, cache);
    result = cache->factors[index];
  }
  else {
    numberOfFactors = getPrimeFactors(n, &factors);
    result = factors;
  }

  // We use a mutex to guarantee that output will appear in order
  if(outputMutex != NULL) {
    pthread_mutex_lock(outputMutex);
  }

  printf("%llu: ", n);
  for (int i = 0; i < numberOfFactors; ++i) {
    printf("%llu ", result[i]);
  }

  printf("\n");
  if(outputMutex != NULL) {
    pthread_mutex_unlock(outputMutex);
  }
}
