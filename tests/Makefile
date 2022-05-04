CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -I ../include/
LDFLAGS = 

TESTS =	bloc

SRC = $(TESTS:=.c) $(wildcard ../obj/%.o)
OBJ = $(TESTS:=.o)

all: $(TESTS)

%-test: %.o
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $^

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)
