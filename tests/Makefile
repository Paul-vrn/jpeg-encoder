CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include -O0 -g
LDFLAGS = -lm
TESTS = mcu
all: $(TESTS)



mcu: mcu.o ../obj/bloc.o ../obj/mcu.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

bloc: bloc.o ../obj/bloc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 


$(TESTS).o: $(TESTS).c 
	$(CC) $(CFLAGS) -c $^ -o $@

#../obj/$(TESTS).o: ../src/$(TESTS).c
#	make -f ../Makefile $@

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)