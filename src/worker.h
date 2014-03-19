#ifndef WORKER_H
#define WORKER_H

#include <stdint.h>

/**
 * Initialize the working context, taking as input the given file.
 */
void initContext(FILE * file);

void printPrimeFactors(uint64_t n);

void * startJob(void * arg);

/*
 * Run two concurrent file, factorizing primes read from the file
 * set in `initContext`.
 */
void runTwoJobs();

#endif