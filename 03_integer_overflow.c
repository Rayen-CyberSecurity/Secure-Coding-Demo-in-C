/*
 * Secure coding example 03 Integer overflow before allocation.
 *
 * Computing an allocation size as count * size can overflow and wrap around
 * to a small number. malloc then returns a tiny buffer, but the code writes
 * count*size bytes -> heap buffer overflow.
 * The fix: check for overflow BEFORE multiplying.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

/* SAFE allocation: rejects the request if count * size would overflow. */
void *alloc_array_safe(size_t count, size_t size) {
    if (size != 0 && count > SIZE_MAX / size) {
        printf("[safe] rejected: count * size would overflow\n");
        return NULL;
    }
    return malloc(count * size);   /* multiplication is now known to be safe */
}

int main(void) {
    void *ok = alloc_array_safe(10, sizeof(int));
    printf("[safe] normal request: %s\n", ok ? "allocated" : "failed");
    free(ok);

    void *bad = alloc_array_safe(SIZE_MAX, 2);
    printf("[safe] overflow request: %s\n", bad ? "allocated" : "rejected");
    free(bad);
    return 0;
}
