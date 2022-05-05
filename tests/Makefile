CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include -O0 -g
LDFLAGS = -lm

#A CHANGER POUR LE CHAQUE TEST
TESTS = mcu \
		bloc
#ASSOCIATED = ../obj/bloc.o ../obj/mcu.o
all: $(TESTS)

#$(TESTS): $(TESTS).o $(ASSOCIATED)
#	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

mcu: mcu.o ../obj/bloc.o ../obj/mcu.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 


$(TESTS).o: $(TESTS).c 
	$(CC) $(CFLAGS) -c $^ -o $@

../obj/%.o: ../src/%.c
	make -f ../Makefile $@

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)
