#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../aoc.h"

int part1(char* data) {
  uint64_t total = 0;
  for (char* ch = data; *ch != 0; ch++ ) {
    char line[16];
    size_t i= 0;
    while (*ch != '\n') {
      line[i++] = *ch++;
    } 
    line[i] = 0;

    int l, b, h;
    sscanf(line, "%dx%dx%d", &l, &b, &h);
    int areas[] = {l*b, b*h, l*h};
    int min_area = MIN_ELEM(areas, ARR_LEN(areas));
    total += 2 * (l*b + b*h + l*h) + min_area;
  }
  return total;
}

int part2(char* data) {
uint64_t total = 0;
  for (char* ch = data; *ch != 0; ch++ ) {
    char line[16];
    size_t i= 0;
    while (*ch != '\n') {
      line[i++] = *ch++;
    } 
    line[i] = 0;

    int l, b, h;
    sscanf(line, "%dx%dx%d", &l, &b, &h);
    int perimeters[] = {2*(l+b), 2*(b+h), 2*(l+h)};
    int min_peri = MIN_ELEM(perimeters, ARR_LEN(perimeters));
    total += l * b * h + min_peri;
  }
  return total;

}

int main(int argc, char** argv) {
  char* input_file = argv[1];
  char* data = read_to_str(input_file);

  printf("Part 1: %d\n", part1(data));
  printf("Part 2: %d\n", part2(data));
  return 0;
}


