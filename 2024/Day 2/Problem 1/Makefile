CC=gcc
CFLAGS=-I.

.PHONY: clean

run: main.out
	./main.out

main.out: main.c
	$(CC) $(CFLAGS) main.c -o main.out

clean:
	rm main.out