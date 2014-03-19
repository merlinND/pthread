#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "primes.h"
#include "worker.h"


// ----- Structures
// Memoization
// TODO: a data structure that could hold the previous factorization results

// ----- Constants
#define MAX_FACTORS 64

// ----- Module-wide variables
static FILE * f;
static pthread_mutex_t readMutex, outputMutex;

void initContext(FILE * file) {
  f = file;

  pthread_mutex_init(&readMutex, NULL);
  pthread_mutex_init(&outputMutex, NULL);
}

void printPrimeFactors(uint64_t n) {
  uint64_t factors[MAX_FACTORS];
  int numberOfFactors = getPrimeFactors(n, factors);

  // We use a mutex to guarantee that output will appear in order
  pthread_mutex_lock(&outputMutex);
  printf("%llu: ", n);
  for (int i = 0; i < numberOfFactors; ++i) {
    printf("%llu ", factors[i]);
  }
  printf("\n");
  pthread_mutex_unlock(&outputMutex);
}

void * startJob(void * arg) {
  uint64_t number;
  int status = 0;
  while(status != -1) {
    // Get mutex in order to read into file
    pthread_mutex_lock(&readMutex);
    status = fscanf(f, "%llu", &number);
    // Release the mutex as quickly as possible
    pthread_mutex_unlock(&readMutex);

    if (status != -1) {
      printPrimeFactors(number);
    }
  }

  return 0;
}

void runTwoJobs() {
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, startJob, NULL);
  pthread_create(&thread2, NULL, startJob, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread1, NULL);
}