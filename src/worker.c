#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <stdlib.h>

#include "primes.h"
#include "worker.h"

// ----- Constants

// ----- Module-wide variables
static FILE * f;
static pthread_mutex_t readMutex, outputMutex;

void initWorkerContext(FILE * file) {
  f = file;

  pthread_mutex_init(&readMutex, NULL);
  pthread_mutex_init(&outputMutex, NULL);
}

void freeWorkerContext() {
  if (f != NULL)
    fclose(f);

  pthread_mutex_destroy(&readMutex);
  pthread_mutex_destroy(&outputMutex);
}

void * startLazyJob(void * arg) {
  uint64_t number =  * (uint64_t *) arg;
  printPrimeFactors(number, &outputMutex, NULL);
  return 0;
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
      printPrimeFactors(number, &outputMutex, NULL);
    }
  }

  return 0;
}

void runTwoLazyJobs() {
  pthread_t thread1, thread2;
  uint64_t number1, number2;

  while(fscanf(f, "%llu", &number1) != -1) {
    pthread_create(&thread1, NULL, startLazyJob, (void *) &number1);

    if (fscanf(f, "%llu", &number2) != -1) {
      pthread_create(&thread2, NULL, startLazyJob, (void *) &number2);
      pthread_join(thread2, NULL);
    }

    pthread_join(thread1, NULL);
  }
}

void runMultipleJobs(int workers) {
  pthread_t * threads = malloc(sizeof(pthread_t) * workers);
  for(int i = 0; i < workers; i ++) {
    pthread_t thread;
    pthread_create(&thread, NULL, startJob, NULL);
    threads[i] = thread;
  }
  for(int i = 0; i < workers; i ++) {
    pthread_t thread;
    thread = threads[i];
    pthread_join(thread, NULL);
  }
  free(threads);
}
