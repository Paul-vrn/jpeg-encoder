CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -I../include -O0 -g
LDFLAGS = -lm
TESTS = mcu bloc vector convert_RGB_to_YCbCr jpg_write frequential_bloc
all: $(TESTS)

mcu: mcu.o ../obj/bloc.o ../obj/mcu.o ../obj/frequential_bloc.o \
			../obj_prof/huffman_prof.o ../obj/vector.o ../obj/encoding.o \
			../obj_prof/bitstream_prof.o ../obj_prof/htables_prof.o \

	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

bloc: bloc.o ../obj/bloc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) 

vector: vector.o ../obj/encoding.o ../obj_prof/jpeg_writer_prof.o \
					 ../obj_prof/bitstream_prof.o ../obj_prof/htables_prof.o \
					 ../obj_prof/huffman_prof.o \
					 ../obj/mcu.o ../obj/vector.o ../obj/bloc.o \
					 ../obj/frequential_bloc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

convert_RGB_to_YCbCr: convert_RGB_to_YCbCr.o ../obj/convert_RGB_to_YCbCr.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

encoding: encoding.o ../obj/encoding.o ../obj_prof/jpeg_writer_prof.o \
					 ../obj_prof/bitstream_prof.o ../obj_prof/htables_prof.o \
					 ../obj_prof/huffman_prof.o ../obj/vector.o \
					 ../obj/mcu.o ../obj/vector.o ../obj/bloc.o \
					 ../obj/frequential_bloc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

jpg_write: jpg_write.o ../obj/bloc.o ../obj_prof/jpeg_writer_prof.o \
					   ../obj_prof/bitstream_prof.o ../obj_prof/huffman_prof.o\
					   ../obj_prof/htables_prof.o ../obj/read_param.o ../obj/read_pic.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
write: write.o ../obj/jpeg_write.o ../obj/huffman_tree.o \
				../obj_prof/htables_prof.o ../obj/read_pic.o ../obj/read_param.o \
				../obj/bitstream_e.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

frequential_bloc: frequential_bloc.o ../obj/frequential_bloc.o ../obj/bloc.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.c 
	$(CC) $(CFLAGS) -c $^ -o $@


#../obj/$(TESTS).o: ../src/$(TESTS).c
#	make -f ../Makefile $@

.PHONY: clean

clean:
	rm -rf *.o *~ $(TESTS)
