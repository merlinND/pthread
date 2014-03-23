#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "sequential.h"
#include "worker.h"
#include "memoized.h"

void sequentialRun(FILE * f) {
  initSequentialContext(f);
  runOneJob();
  freeSequentialContext(f);
}

void lazyRun(FILE * f) {
  initWorkerContext(f);
  runTwoLazyJobs();
  freeWorkerContext(f);
}

void workerRun(FILE * f, int numberOfThreads) {
  initWorkerContext(f);
  runMultipleJobs(numberOfThreads);
  freeWorkerContext(f);
}

void memoizedRun(FILE * f) {
  initMemoizedContext(f);
  runMemoizedJobs();
  freeMemoizedContext(f);
}

int main(int argc, char **argv) {
  FILE * f = stdin;
  if(f != NULL) {
    char command;
    if((command = getopt(argc, argv, "slmw:")) != -1) {
      switch(command) {
        case 's':
          sequentialRun(f);
          break;
        case 'l':
          lazyRun(f);
          break;
        case 'w':
          workerRun(f, atoi(optarg));
          break;
        case 'm':
          memoizedRun(f);
          break;
      }
    } else {
      memoizedRun(f);
    }
  } else {
    perror("Error opening input file.");
    return 1;
  }
  return 0;
}
