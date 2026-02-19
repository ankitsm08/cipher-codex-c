SRC := "src/main.c src/cipher.c src/ciphers/*.c"
BIN := "cipher"

default:
  @just --list

build:
  cc -Iinclude -std=c11 -Wall -Wextra {{SRC}} -o {{BIN}}

build-db:
  bear -- just build

run: build
  ./{{BIN}}

clean:
  rm -f {{BIN}} compile_commands.json

