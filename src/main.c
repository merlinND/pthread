#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "sequential.h"
#include "worker.h"

int main(int argc, char **argv) {
  FILE * f = stdin;
  if(f != NULL) {
    char command;
    if((command = getopt(argc, argv, "slw:")) != -1) {
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
