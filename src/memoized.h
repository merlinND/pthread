#ifndef MEMOIZED_H
#define MEMOIZED_H

#include <stdio.h>

void initMemoizedContext(FILE * file);
void freeMemoizedContext(FILE * file);

void runMemoizedJobs(int workers);

#endif