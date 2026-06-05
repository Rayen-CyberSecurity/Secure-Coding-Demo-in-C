# Secure-Coding-Demo-in-C

A small **secure coding demo in C**: shows the classic buffer overflow
caused by unchecked copying (`strcpy`) and the safe version using a
**length check** and **input validation** (a whitelist of allowed characters).
In embedded C programs this is one of the most important secure-coding rules.

## Build & run
    gcc -Wall -Wextra -o secure-input secure-input.c && ./secure-input

## Core rules (secure coding)
1. Never copy into a fixed buffer unchecked -> avoid `strcpy`
2. Check the input length BEFORE copying
3. Validate input (whitelist instead of blacklist)
4. Use safe functions (`snprintf` instead of `strcpy`)
