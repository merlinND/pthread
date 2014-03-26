#ifndef PRIMES_H
#define PRIMES_H

#include <stdint.h>
#include <pthread.h>

#include "cache.h"

// ----- Functions
int isPrime(uint64_t p);

int getPrimeFactors(uint64_t n, uint64_t * destination);
int getMemoizedPrimeFactors(uint64_t n, map_t * cache, uint64_t ** result);

void printPrimeFactors(uint64_t n, pthread_mutex_t * outputMutex, map_t * cache);

#endif
