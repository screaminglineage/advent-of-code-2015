#include <stdio.h>
#include <stdlib.h>
#include "../aoc.h"

int part1(char* data) {
  int floor = 0;
  for (char* ch = data; *ch != 0; ch++ ) {
    if (*ch == '(') {
      floor++;
    } else if (*ch == ')') {
      floor--;
    }   
  }
  return floor;
}

int part2(char* data) {
  int floor = 0;
  int i;
  for (i = 0; data[i] != 0; i++ ) {

    if (data[i] == '(') {
      floor++;
    } else if (data[i] == ')') {
      floor--;
    }
    if (floor == -1) {
      break;
    }
  }

  return i+1;

}

int main(int argc, char** argv) {
  char* input_file = argv[1];
  char* data = read_to_str(input_file);

  printf("Part 1: %d\n", part1(data));
  printf("Part 2: %d\n", part2(data));
  return 0;
}


