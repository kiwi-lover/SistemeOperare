CC = gcc
CFLAGS = -Wall -O2

all: mytr_mmap myhead_mmap

mytr_mmap: mytr_mmap.c
	$(CC) $(CFLAGS) -o mytr_mmap mytr_mmap.c

myhead_mmap: myhead_mmap.c
	$(CC) $(CFLAGS) -o myhead_mmap myhead_mmap.c

clean:
	rm -f mytr_mmap myhead_mmap
