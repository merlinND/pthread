#ifndef WORKER_H
#define WORKER_H

#include <stdint.h>

/**
 * Initialize the working context, taking as input the given file.
 */
void initWorkerContext(FILE * file);

/*
 * Read two numbers and start a job to factorize each number.
 * Wait for both jobs to finish.
 * Repeat until all numbers have been read from the file.
 */
void runTwoLazyJobs();

/*
 * Run two concurrent file, factorizing primes read from the file
 * set in `initContext`.
 */
void runTwoJobs();

#endif
