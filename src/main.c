#include <stdio.h>

#include "worker.h"

int main() {
  FILE * f = stdin;
  if(f != NULL) {
    initContext(f);
    runTwoJobs();
  } else {
    perror("Error opening input file.");
  }
}
