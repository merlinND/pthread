#include "memoized.h"

#include "cache.h"
#include "primes.h"

// ----- Module-wide variables
static FILE * f;
static map_t cache;
static pthread_mutex_t outputMutex;

void initMemoizedContext(FILE * file) {
  f = file;
  cache = hashmap_new();
  pthread_mutex_init(&outputMutex, NULL);
}
void freeMemoizedContext(FILE * file) {
  if (f!= NULL)
    fclose(f);

  // TODO: free each entry of the cache

  hashmap_free(cache);
  pthread_mutex_destroy(&outputMutex);
}

// TODO: replace sequential run by concurrent threads (sync access to the cache) 
void runMemoizedJobs() {
  uint64_t number;
  int status = 0;
  while(status != -1) {
    status = fscanf(f, "%llu", &number);
    if (status != -1) {
      printPrimeFactors(number, &outputMutex, cache);
    }
  }
}