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
    bear -- make

run: build
    ./{{ BIN }}

clean:
    rm -f {{ BIN }} compile_commands.json
