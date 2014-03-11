#include <stdio.h>
#include <stdint.h>
#include <math.h>

int isPrime(uint64_t p) {
	for (uint64_t i = 2; i <= sqrt(p); ++i) {
		if (p % i == 0)
			return 0;
	}
	return 1;
}

int main() {
	printf("Testing for primality:\n");
	for (uint64_t i = 1; i < 11; ++i) {
		printf("%d is prime: %d\n", i, isPrime(i));
	}
}
