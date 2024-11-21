md5: md5.c
	gcc -O3 -c -o md5.o md5.c

all: md5.o
	gcc -O3 -o main -lm md5.o main.c

run: all
	./main "data.txt"

clean:
	rm main *.o
