# Cipher Codex (C)

**Security Disclaimer**: This project is for educational purposes. The implemented ciphers are not secure for real-world cryptographic use.

**TL;DR**: A modular C library of classical and modern ciphers. Fully data-driven, CLI-ready, and easy to extend. Heap-allocated strings, explicit memory rules, and no giant if/else chains.

A modular, extensible collection of classical and modern cipher implementations written in **C**, with a clean registry-based architecture.

This project is me exploring low-level systems design applied to cryptography:

- manual memory management
- function pointers
- data-driven dispatch
- clear ABI-style contracts

No frameworks. No magic. Just C.

---

## Features

- **Plugin-style cipher registry**
- **Data-driven dispatch** (no giant `if/else` chains)
- Clean separation between:
  - cipher implementations
  - registry
  - user interface
- Each cipher is self-contained
- Explicit memory ownership rules
- Easy to extend with new algorithms
- On failure, cipher functions return `NULL` and do not modify global state.

I ran into a lack of a clean, easy-to-use system for managing ciphers when I was making a cipher codex in C++.

---

## Project Structure

```bash
.
├── include/
│   ├── ciphers/    # Cipher specific headers
│   │   └── *.h
│   └── cipher.h    # Core cipher interface and registry API
├── src/
│   ├── ciphers/    # Cipher implementations
│   │   └── *.c
│   ├── cipher.c    # Core registry and API implementation
│   └── main.c      # CLI interface
├── tests/
└── justfile        # Build recipes
```

---

## Requirements

- Unix-like OS (Linux/macOS) for `cc` and `just` usage
- C11-compatible compiler
- Optional: [just](https://github.com/casey/just) and [bear](https://github.com/rizsotto/Bear) for build automation

## 🔧 Build & Run

Run from project root:

```bash
# Build
cc -Iinclude -std=c11 -Wall -Wextra \
   src/main.c src/cipher.c src/ciphers/*.c \
   -o cipher

# Run
./cipher
```

If using `just` (recommended):

```bash
# List available recipes
just --list

# Only build
just build

# Generate compile_commands.json
#! Requires `bear` to be installed
just build-db

# Build and run
just run

# Clean
just clean
```

Demo run of the CLI:

```bash
$ ./cipher
Operations:
1. Encrypt
2. Decrypt
Choose the operation: 1
Available Ciphers:
[1] Caesar
[2] ROT13
[3] Atbash
[4] Affine
Enter the cipher id: 4
Enter your message:
This is my message.
Do you have a problem with it?

Enter the number 1: 3
Enter the number 2: 5
Result:
Kadh dh pz prhhfxr.
Ov zvn afqr f yevimrp tdka dk?
```

## Design Philosophy

### Cipher Interface Contract

All ciphers conform to this function signature:

```c
char *encrypt(const char *input, const cipher_params_t *params);
char *decrypt(const char *input, const cipher_params_t *params);
```

Rules:

- `input` and `params` are read-only
- Returned string is heap-allocated
- Caller is responsible for `free()`

This mirrors real-world C library ABI design.

### Cipher Registry

Ciphers are registered centrally:

```c
static cipher_t cipher_registry[] = {
    {"Caesar", PARAM_NUMBER, caesar_encrypt, caesar_decrypt},
    {"ROT13", PARAM_NONE, rot13_encrypt, rot13_decrypt},
    {"Atbash", PARAM_NONE, atbash_encrypt, atbash_decrypt},
    ...
};
```

The CLI discovers available ciphers dynamically.
Adding a new cipher does not require modifying `main.c`.
This is the key feature of this project which was the reason for me abandoning my previous project in C++.
Also abandoned it because C++ wasn’t the best fit for this kind of modular registry-based design.

### Example Usage

See main.c file for full example.

```c
const cipher_t *cipher = get_cipher(0);
cipher_params_t params = { .number = 3 };
char *result = cipher->encrypt("Hello", &params);
```

## Implemented Ciphers

### Classical

#### Simple

- Affine
  - ROT13
  - Atbash
  - Caesar

<!-- For later --
#### Mechanical

### Modern

#### Symmetric

#### Hash and Integrity

#### Asymmetric

#### Elliptic Curve
-->

More classical and modern ciphers planned.

## Future Ideas?

- File-based input
- File-based output

## Further Reading

### Programming, Design and Computing

- [ABI (Application Binary Interface)](https://en.wikipedia.org/wiki/Application_binary_interface)
- [Plugin-style architectures](<https://en.wikipedia.org/wiki/Plug-in_(computing)>)

### C Language

- [C Programming Language](https://en.wikipedia.org/wiki/C_Programming_Language)
- [Function pointers in C](https://www.geeksforgeeks.org/function-pointer-in-c/)
- [Memory management in C](https://www.w3schools.com/c/c_memory_management.php)

### Cryptograhy

- [Kerckhoffs's Principle](https://en.wikipedia.org/wiki/Kerckhoffs's_principle)

### Math

- [Extended Euclidean Algorithm](https://en.wikipedia.org/wiki/Extended_Euclidean_algorithm)

## License

MIT License
