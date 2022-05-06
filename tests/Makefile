CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include -O0 -g
LDFLAGS = -lm
#TESTS = mcu bloc vector read_param frequential_bloc
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

frequential_bloc: frequential_bloc.o ../obj/frequential_bloc.o ../obj/bloc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TESTS).o: $(TESTS).c 
	$(CC) $(CFLAGS) -c $^ -o $@


#../obj/$(TESTS).o: ../src/$(TESTS).c
#	make -f ../Makefile $@

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)
