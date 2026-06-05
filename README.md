# Secure-Coding-Demo-in-C

A small collection of classic **secure coding** mistakes in C, each shown as a
vulnerable pattern next to its safe fix. These are common, high-impact bugs in
embedded and systems software — the kind that lead to crashes, memory
corruption, and exploitable vulnerabilities.

## Examples

| # | File | Topic |
|---|------|-------|
| 01 | `01_buffer_overflow.c` | Buffer overflow — length check and input validation |
| 02 | `02_format_string.c` | Format string vulnerability (`printf(user_input)`) |
| 03 | `03_integer_overflow.c` | Integer overflow before a memory allocation |
| 04 | `04_constant_time_compare.c` | Cryptography — constant-time comparison (timing attacks) |

## Build & run

Each example is self-contained and compiles on its own:

    gcc -Wall -Wextra -o demo 01_buffer_overflow.c && ./demo

Replace the filename to run a different example, for example:

    gcc -Wall -Wextra -o demo 04_constant_time_compare.c && ./demo

## What each example teaches

- **01 — Buffer overflow:** Never copy into a fixed buffer unchecked. Check the
  input length before copying, validate the content (whitelist), and use safe
  functions like `snprintf` instead of `strcpy`.
- **02 — Format string:** Never pass user input as the format string. Always
  pass it as an argument: `printf("%s", input)`, not `printf(input)`.
- **03 — Integer overflow:** `count * size` can overflow and wrap to a small
  value, leading to an undersized allocation and a heap overflow. Check for
  overflow before multiplying.
- **04 — Constant-time comparison:** Comparing secrets (tokens, passwords, HMAC
  tags) with `memcmp`/`strcmp` stops at the first differing byte, which leaks
  timing an attacker can exploit. Compare in constant time, scanning every byte.

## Notes

Example 02 intentionally triggers the compiler's `-Wformat-security` warning —
that warning is exactly the tool that helps catch this class of bug.
