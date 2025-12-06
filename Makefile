CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -g
SRC = src/main.c src/circuit.c
OBJ = $(SRC:.c=.o)
TARGET = wnandopt

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(TARGET)

.PHONY: all clean
