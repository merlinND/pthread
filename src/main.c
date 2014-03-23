#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "sequential.h"
#include "worker.h"
#include "memoized.h"

void sequencialRun(FILE * f) {
  initSequentialContext(f);
  runOneJob();
  freeSequentialContext(f);
}

void lazyRun(FILE * f) {
  initWorkerContext(f);
  runTwoLazyJobs();
  freeWorkerContext(f);
}

void workerRun(FILE * f) {
  initWorkerContext(f);
  runMultipleJobs(2);
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
          initSequentialContext(f);
          runOneJob();
          break;
        case 'l':
          initWorkerContext(f);
          runTwoLazyJobs();
          break;
        case 'w':
          initWorkerContext(f);
          runMultipleJobs(atoi(optarg));
          break;
        case 'm':
          memoizedRun(f);
          break;
      }
    } else {
      initWorkerContext(f);
      runMultipleJobs(4);
    }
  } else {
    perror("Error opening input file.");
    return 1;
  }
  return 0;
}
