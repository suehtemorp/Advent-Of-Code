CC=g++
CFLAGS=-I.

.PHONY: clean

run: main.out
	./main.out

main.out: main.cpp 
	$(CC) $(CFLAGS) main.cpp -o main.out

clean:
	rm main.out