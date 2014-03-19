#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

#include "primes.h"

#define MAX_FACTORS 64

// ----- Structures
// Memoization
// TODO: a data structure that could hold the previous factorization results

// ----- Module-wide variables
static FILE * f;
static pthread_mutex_t readMutex, outputMutex;

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
      printPrimeFactors(number);
    }
  }
}

void runTwoJobs() {
  pthread_mutex_init(&readMutex, NULL);
  pthread_mutex_init(&outputMutex, NULL);

  pthread_t thread1, thread2;
  pthread_create(&thread1, NULL, startJob, NULL);
  pthread_create(&thread2, NULL, startJob, NULL);
  pthread_join(thread2, NULL);
  pthread_join(thread1, NULL);
}

int main() {
  f = stdin;
  if(f != NULL) {
    runTwoJobs();
  } else {
    perror("Error opening input file.");
  }
}
