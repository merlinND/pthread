#include <stdio.h>
#include <unistd.h>

#include "sequential.h"
#include "worker.h"


void sequencialRun(FILE * f) {
  initSequentialContext(f);
  runOneJob();
}

void workerRun(FILE * f) {
  initWorkerContext(f);
  runTwoJobs();
}


int main(int argc, char **argv) {
  FILE * f = stdin;
  if(f != NULL) {
    char command;
    if((command = getopt(argc, argv, "sw")) != -1) {
      switch(command) {
        case 's':
          sequencialRun(f);
          break;
        case 'w':
          workerRun(f);
          break;
      }
    } else {
      workerRun(f);
    }
  } else {
    perror("Error opening input file.");
    return 1;
  }
  return 0;
}
