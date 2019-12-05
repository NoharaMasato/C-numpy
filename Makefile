CC = gcc
CFLAGS = $(shell python3.7-config --cflags) -I/usr/local/lib/python3.7/site-packages/numpy/core/include
LDFLAGS = $(shell python3.7-config --ldflags)

main:
	$(CC) $(CFLAGS) $(LDFLAGS) main.c

