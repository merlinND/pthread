#ifndef WORKER_H
#define WORKER_H

#include <stdint.h>

/**
 * Initialize the working context, taking as input the given file.
 */
void initWorkerContext(FILE * file);
void freeWorkerContext();

/*
 * Read two numbers and start a job to factorize each number.
 * Wait for both jobs to finish.
 * Repeat until all numbers have been read from the file.
 */
void runTwoLazyJobs();

/*
 * Run concurrent file readings, factorizing primes read from the file
 * set in `initContext`.
 * @param workers The amount of parallel workers started
 */
void runMultipleJobs(int workers);

#endif
