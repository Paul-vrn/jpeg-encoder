CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include -O0 -g
LDFLAGS = -lm
<<<<<<< HEAD
TESTS = mcu bloc vector read_param
=======
TESTS = mcu bloc vector
>>>>>>> 08d9d60592a4654ecf13c669ce31a3e3e838f296
all: $(TESTS)



mcu: mcu.o ../obj/bloc.o ../obj/mcu.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

bloc: bloc.o ../obj/bloc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

read_param: read_param.o ../obj/read_param.o ../obj/read_pic.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

vector: vector.o ../obj/bloc.o ../obj/vector.o
zig_zag: zig_zag.o ../obj/bloc.o ../obj/zig_zag.o ../obj/mcu.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

vector: vector.o ../obj/bloc.o ../obj/vector.o ../obj_prof/htables_prof.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TESTS).o: $(TESTS).c 
	$(CC) $(CFLAGS) -c $^ -o $@

#../obj/$(TESTS).o: ../src/$(TESTS).c
#	make -f ../Makefile $@

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)
