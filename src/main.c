#include <stdio.h>

#include "sequential.h"

int main() {
  FILE * f = stdin;
  if(f != NULL) {
    initSequentialContext(f);
    runOneJob();
  } else {
    perror("Error opening input file.");
  }
}
