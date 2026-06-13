set shell := ["bash", "-euo", "pipefail", "-c"]

FILES := "src/*.c src/ciphers/*.c src/utils/*.c include/*.h include/ciphers/*.h include/utils/*.h"
BIN := "cipher"

default:
    @just --list

format:
    clang-format -i {{ FILES }}

lint:
    clang-tidy {{ FILES }} --checks='*' -- -Iinclude

build:
    make

build-db:
    @just clean
    rm -f compile_commands.json
    bear -- just build

run: build
    ./{{ BIN }}

clean:
    make clean
