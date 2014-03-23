#ifndef MEMOIZED_H
#define MEMOIZED_H

#include <stdio.h>

void initMemoizedContext(FILE * file);
void runMemoizedJobs();
void freeMemoizedContext(FILE * file);

#endif