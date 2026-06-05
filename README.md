# Secure-Coding-Demo-in-C
Shows the classic C security problem : a buffer overflow caused by  copying without checking the length  and the safe version that  validates length and input before copying. In embedded C programs this  is one of the most important secure-coding rules.

secure-input

A small **secure coding demo in C**: shows the classic buffer overflow
caused by unchecked copying (`strcpy`) and the safe version using a
**length check** and **input validation** (whitelist of allowed characters).

## Build
    gcc -Wall -Wextra -o secure_input secure_input.c && ./secure_input

## Core rules (secure coding)
1. Never copy into a fixed buffer unchecked -> avoid `strcpy`
2. Check the input length BEFORE copying
3. Validate input (whitelist instead of blacklist)
