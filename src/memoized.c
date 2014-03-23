#include "memoized.h"

#include "cache.h"
#include "primes.h"

// ----- Module-wide variables
static FILE * f;
static map_t cache;
static pthread_mutex_t readMutex, outputMutex;

void initMemoizedContext(FILE * file) {
  f = file;
  cache = hashmap_new();
  pthread_mutex_init(&readMutex, NULL);
  pthread_mutex_init(&outputMutex, NULL);
}
void freeMemoizedContext(FILE * file) {
  if (f!= NULL)
    fclose(f);

  freeCache(cache);
  pthread_mutex_destroy(&readMutex);
  pthread_mutex_destroy(&outputMutex);
}

void * startMemoizedJob(void * arg) {
  uint64_t number;
  int status = 0;
  while(status != -1) {
    // Get mutex in order to read into file
    pthread_mutex_lock(&readMutex);
    status = fscanf(f, "%llu", &number);
    // Release the mutex as quickly as possible
    pthread_mutex_unlock(&readMutex);

    if (status != -1) {
      printPrimeFactors(number, &outputMutex, cache);
    }
  }

  return 0;
}

void runMemoizedJobs(int workers) {
  pthread_t * threads = malloc(sizeof(pthread_t) * workers);
  for(int i = 0; i < workers; i ++) {
    pthread_t thread;
    pthread_create(&thread, NULL, startMemoizedJob, NULL);
    threads[i] = thread;
  }
  for(int i = 0; i < workers; i ++) {
    pthread_t thread;
    thread = threads[i];
    pthread_join(thread, NULL);
  }
  free(threads);
}