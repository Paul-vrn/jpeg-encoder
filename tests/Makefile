CC = gcc
CFLAGS = -Wall -Wextra -g -O2 -I../include
LDFLAGS = -lm

#A CHANGER POUR LE CHAQUE TEST
TESTS = mcu
ASSOCIATED = ../obj/bloc.o ../obj/mcu.o
all: $(TESTS)

$(TESTS): $(TESTS).o $(ASSOCIATED)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

$(TESTS).o: $(TESTS).c 
	$(CC) $(CFLAGS) -c $^ -o $@

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)
