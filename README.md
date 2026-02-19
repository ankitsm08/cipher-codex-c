# Cipher Codex (C)

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

```bash
# Build
cc -Iinclude -std=c11 -Wall -Wextra \
   src/main.c src/cipher.c src/ciphers/*.c \
   -o cipher

# Run
./cipher
```

If using just:

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

```bash
$ ./cipher
Available Ciphers:
[0] Caesar
Enter the cipher id: 0
Enter your message:
Hello World
Enter the key: 3
Result:
Khoor Zruog
```

## Design Philosophy

### Cipher Interface Contract

All ciphers conform to this function signature:

```cpp
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

```cpp
static cipher_t cipher_registry[] = {
    {"Caesar", PARAM_NUMBER, caesar_encrypt, caesar_decrypt},
    ...
};
```

The CLI discovers available ciphers dynamically.
Adding a new cipher does not require modifying `main.c`.
This is the key feature of this project which was the reason for me abandoning my previous project in C++.
Also abandoned it because C++ wasn’t the best fit for this kind of modular registry-based design.

## Implemented Ciphers

- Caesar Cipher (shift-based)

More classical and modern ciphers planned.

## Future Ideas?

- File-based input
- File-based output

## Further Reading

- [C Programming Language](https://en.wikipedia.org/wiki/C_Programming_Language)
- [Function pointers in C](https://www.geeksforgeeks.org/function-pointer-in-c/)
- [Memory management in C](https://www.w3schools.com/c/c_memory_management.php)
- [ABI (Application Binary Interface)](https://en.wikipedia.org/wiki/Application_binary_interface)
- [Plugin-style architectures](<https://en.wikipedia.org/wiki/Plug-in_(computing)>)

## License

MIT License
