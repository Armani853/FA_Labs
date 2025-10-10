#include "functions.h"
#include <stdlib.h>
#include <math.h>

StatusCode is_prime(long num) {
    if (num <= 1) {
        return INVALID_INPUT;
    }
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) {
            return NOT_PRIME;
        }
        
    }
    return STATUS_OK;
}

StatusCode find_n_prime(long n, long* result) {
    if (n < 1) {
        return INVALID_INPUT;
    }
    if (n > 100000) {
        return OUT_OF_RANGE;
    }
    const long limit = 1500000;
    char* sieve = (char*)malloc(limit * sizeof(char));
    if (sieve == NULL) {
        return MEMORY_ERROR;
    }
    for (long i = 0; i < limit; i++) {
        sieve[i] = 1;
    }
    sieve[0] = sieve[1] = 0;

    for (long i = 2; i * i < limit; i++) {
        if (sieve[i]) {
            for (long j = i * i; j < limit; j += i) {
                sieve[j] = 0;
            }
        }
    }

    long* primes = (long*)malloc(100001 * sizeof(long));
    if (primes == NULL) {
        free(sieve);
        return MEMORY_ERROR;
    }
    int count = 0;
    for (long i = 2; i < limit && count < n; i++) {
        if (sieve[i]) {
            primes[count] = i;
            count++;
        }
    }
    free(sieve);
    if (count < n) {
        free(primes);
        return OUT_OF_RANGE;
    }
    *result = primes[n - 1];
    free(primes);
    return STATUS_OK;
}

