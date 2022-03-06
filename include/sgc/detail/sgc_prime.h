#pragma once
#include <stdbool.h>
#include <stdlib.h>

static float sgc_abs(float num) {
    return (num < 0) ? -num : num;
}

static size_t sgc_sqrt(int n) {
    const float diff = 1;
    float guess = 1;
    while (sgc_abs(guess * guess - n) >= diff) {
        guess = (n / guess + guess) / 2.0;
    }
    return (int)(guess) + 1;
}

static bool sgc_is_prime(size_t n) {
    int is_prime = false;
    for (size_t i = 2; i <= sgc_sqrt(n); ++i) {
        if (n % i == 0) {
            is_prime = true;
            break;
        }
    }
    return is_prime;
}

static size_t sgc_next_prime(size_t n) {
    while (!sgc_is_prime(n)) {
        ++n;
    }
    return n;
}
