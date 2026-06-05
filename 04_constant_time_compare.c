/*
 * Secure coding example 04 - Cryptography: constant-time comparison.
 *
 * Comparing secrets (passwords, API tokens, HMAC tags) with memcmp/strcmp is
 * dangerous: those functions stop at the FIRST differing byte, so the time
 * taken leaks how many leading bytes were correct. An attacker can measure
 * this and guess the secret byte by byte (a timing attack).
 * The fix: a constant-time comparison that always inspects every byte.
 */
#include <stdio.h>
#include <stddef.h>

/*  returns early on the first mismatch, leaking timing. */
int compare_unsafe(const unsigned char *a, const unsigned char *b, size_t len) {
    for (size_t i = 0; i < len; i++)
        if (a[i] != b[i]) return 0;   /* <-- early exit reveals timing */
    return 1;
}

/*  always scans the whole length; time does not depend on the data. */
int compare_constant_time(const unsigned char *a, const unsigned char *b, size_t len) {
    unsigned char diff = 0;
    for (size_t i = 0; i < len; i++)
        diff |= a[i] ^ b[i];          /* accumulate differences, no branch */
    return diff == 0;
}

int main(void) {
    const unsigned char secret[] = "S3CR3T-TOKEN";
    const unsigned char right[]  = "S3CR3T-TOKEN";
    const unsigned char wrong[]  = "S3CR3T-XXXXX";
    size_t len = sizeof(secret) - 1;

    printf("[safe] correct token: %s\n",
           compare_constant_time(secret, right, len) ? "accepted" : "rejected");
    printf("[safe] wrong token:   %s\n",
           compare_constant_time(secret, wrong, len) ? "accepted" : "rejected");
    return 0;
}
