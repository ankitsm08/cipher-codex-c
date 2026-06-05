CC       = cc
CFLAGS   = -Iinclude -std=c11 -Wall -Wextra -fsanitize=address -fsanitize=undefined -g -MMD
LDFLAGS  = -fsanitize=address -fsanitize=undefined
SRC      = $(wildcard src/*.c src/ciphers/*.c)
OBJ      = $(SRC:.c=.o)
DEP      = $(OBJ:.o=.d)
BIN      = cipher

$(BIN): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

-include $(DEP)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -f $(OBJ) $(DEP) $(BIN)
