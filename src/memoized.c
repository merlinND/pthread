#include "memoized.h"

#include "primes.h"

// ----- Module-wide variables
static FILE * f;
static cache_t cache;
static pthread_mutex_t outputMutex;

void initMemoizedContext(FILE * file) {
  f = file;
  cache.size = 0;
  pthread_mutex_init(&outputMutex, NULL);
}

void runMemoizedJobs() {
  uint64_t number;
  int status = 0;
  while(status != -1) {
    status = fscanf(f, "%llu", &number);
    if (status != -1) {
      printPrimeFactors(number, &outputMutex, &cache);
    }
  }
}