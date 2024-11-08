CC = gcc
CFLAGS = -g -pedantic -Wall -Wextra
LDFLAGS = 

SRC = Makef.c 
OBJ = $(SRC:.c=.o)
EXEC = Makef

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(EXEC)

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXEC)

-include dep
