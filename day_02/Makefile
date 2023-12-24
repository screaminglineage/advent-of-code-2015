aoc:
	gcc -o aoc.h.gch ../aoc.h

all: aoc
	gcc -o main main.c

run: all
	./main "data.txt"

clean:
	rm main *.gch
