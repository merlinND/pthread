#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

#include "primes.h"
#include "worker.h"


// ----- Structures
// Memoization
// TODO: a data structure that could hold the previous factorization results

// ----- Constants

// ----- Module-wide variables
static FILE * f;
static pthread_mutex_t readMutex, outputMutex;

void initWorkerContext(FILE * file) {
  f = file;

  pthread_mutex_init(&readMutex, NULL);
  pthread_mutex_init(&outputMutex, NULL);
}

void startJob(void * arg) {
  uint64_t number;
  int status = 0;
  while(status != -1) {
    // Get mutex in order to read into file
    pthread_mutex_lock(&readMutex);
    status = fscanf(f, "%llu", &number);
    // Release the mutex as quickly as possible
    pthread_mutex_unlock(&readMutex);

    if (status != -1) {
      printPrimeFactors(number, &outputMutex);
    }
  }
}

void runTwoJobs() {
  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, startJob, NULL);
  pthread_create(&thread2, NULL, startJob, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread1, NULL);
}
