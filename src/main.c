#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

int isPrime(uint64_t p) {
  for (uint64_t i = 2; i <= sqrt(p); ++i) {
    if (p % i == 0)
      return 0;
  }
  return 1;
}

void printPrimeFactors(uint64_t n) {
  printf("%d: ", n);
  uint64_t i = 2;
  while (n > 1) {
    while (!isPrime(i))
      ++i;
    while (n % i == 0) {
      printf("%d ", i);
      n /= i;
    }
    if (n % i != 0)
      i++;
  }
  printf("\n");
}

void startJob(void * param) {
	uint64_t number = * (uint64_t*) param;
	printPrimeFactors(number);
}

int main() {
  FILE * f = fopen("numbers.txt", "r");
  if(f != NULL) {
    uint64_t number;
    while(fscanf(f, "%llu", &number) != -1) {
	pthread_t thread1, thread2;
      	pthread_create(&thread1, NULL, startJob, (void *) &number);

	if (fscanf(f, "%llu", &number) != -1) {
      		pthread_create(&thread2, NULL, startJob, (void *) &number);
		pthread_join(thread2, NULL);
	}
	pthread_join(thread1, NULL);
    }
    fclose(f);
  } else {
    perror("Error opening numbers.txt");
  }

}
