#ifndef SEQUENTIAL_H
#define SEQUENTIAL_H

#include <stdio.h>

void initSequentialContext(FILE * file);
void freeSequentialContext(FILE * file);

void runOneJob();

#endif
