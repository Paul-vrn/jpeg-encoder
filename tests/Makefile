CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include -O0 -g
LDFLAGS = -lm
#TESTS = mcu bloc vector read_param
all: $(TESTS)



mcu: mcu.o ../obj/bloc.o ../obj/mcu.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

bloc: bloc.o ../obj/bloc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

read_param: read_param.o ../obj/read_param.o ../obj/read_pic.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

vector: vector.o ../obj/bloc.o ../obj/vector.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

zig_zag: zig_zag.o ../obj/bloc.o ../obj/zig_zag.o ../obj/mcu.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

convert_RGB_to_YCbCr: convert_RGB_to_YCbCr.o ../obj/convert_RGB_to_YCbCr.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

encoding: encoding.o ../obj/encoding.o ../obj_prof/jpeg_writer_prof.o \
					 ../obj_prof/bitstream_prof.o ../obj_prof/htables_prof.o \
					 ../obj_prof/huffman_prof.o ../obj/vector.o \
					 ../obj/mcu.o ../obj/vector.o ../obj/bloc.o \
					 ../obj/frequential_bloc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TESTS).o: $(TESTS).c 
	$(CC) $(CFLAGS) -c $^ -o $@

#../obj/$(TESTS).o: ../src/$(TESTS).c
#	make -f ../Makefile $@

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)
