#include <stdio.h>
#include <string.h>
#include <stddef.h>

#define BUF_SIZE 16


/* If the input is longer than the buffer, it writes past the buffer
 * boundary (buffer overflow, undefined behaviour). */
void copy_unsafe(const char *input) {
    char buf[BUF_SIZE];
    strcpy(buf, input);          /*vulnerability */
    printf("[unsafe] copied: %s\n", buf);
}

/* SAFE checks length AND allowed characters before copying.
 * Returns: 1 = ok, 0 = rejected. */
int copy_safe(const char *input, char *out, size_t out_size) {
    if (input == NULL || out == NULL || out_size == 0) return 0;

    /* 1) Length check: does the input fit, including the null terminator? */
    if (strlen(input) >= out_size) {
        printf("[safe]   rejected: input too long\n");
        return 0;
    }
    /* 2) Input validation: allow only letters, digits and '_' */
    for (const char *p = input; *p; p++) {
        char c = *p;
        int ok = (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
              || (c >= '0' && c <= '9') || c == '_';
        if (!ok) {
            printf("[safe]   rejected: invalid character '%c'\n", c);
            return 0;
        }
    }
    /* 3) Safe copy with a fixed destination size */
    snprintf(out, out_size, "%s", input);
    printf("[safe]   accepted: %s\n", out);
    return 1;
}

int main(void) {
    char out[BUF_SIZE];

    printf("Normal input:\n");
    copy_safe("rayen_99", out, sizeof out);

    printf("\nToo-long input (would overflow the unsafe version):\n");
    copy_safe("way_too_long_username", out, sizeof out);

    printf("\nInput with a disallowed character:\n");
    copy_safe("rm -rf /", out, sizeof out);

    return 0;
}
