#include <stdio.h>
#include <stdint.h>
#include <pthread.h>
#include <math.h>

// ----- Module-wide variables
static FILE * f;

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

void startJob(void * arg) {
  pthread_mutex_t * mutex = arg;

  uint64_t number;
  int status = 0;
  while(status != -1) {
    // Get mutex in order to read into file
    pthread_mutex_lock(mutex);
    status = fscanf(f, "%llu", &number);
    // Release the mutex as quickly as possible
    pthread_mutex_unlock(mutex);

    if (status != -1) {
      printPrimeFactors(number);
    }
  }
}

int main() {
  f = fopen("numbers.txt", "r");
  if(f != NULL) {
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    pthread_t thread1, thread2;
    pthread_create(&thread1, NULL, startJob, (void *) &mutex);
    pthread_create(&thread2, NULL, startJob, (void *) &mutex);
    pthread_join(thread2, NULL);
    pthread_join(thread1, NULL);

    fclose(f);
  } else {
    perror("Error opening numbers.txt");
  }
}
