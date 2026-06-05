/*
 * Secure coding example 02 - Format string vulnerability.
 *
 * Passing user input directly as the format string lets an attacker inject
 * format specifiers (%x, %s, %n) to read memory or even write to it.
 * The fix: always pass user data as an ARGUMENT, never as the format string.
 */
#include <stdio.h>

/* user controls the format string. */
void print_unsafe(const char *user_input) {
    printf(user_input);            /*vulnerability: e.g. input "%x %x %x" leaks memory */
    printf("\n");
}

/* user data is an argument; "%s" is the fixed format. */
void print_safe(const char *user_input) {
    printf("%s\n", user_input);
}

int main(void) {
    const char *evil = "value=%x %x %x";   /* contains format specifiers */

    printf("[safe] ");
    print_safe(evil);   /* prints the text literally, specifiers are harmless */
    return 0;
}
