#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../aoc.h"

typedef struct {
  int x;
  int y;
} Point;

typedef struct {
  Point point;
  int count;
} PointCount;

typdef struct {
  PointCount points[1024];
  size_t size;
} AssocArr;

// up, down, left, right
Point DELTAS[] = {
  (Point) { 0, -1 },
  (Point) { 0, 1 },
  (Point) { -1, 0 },
  (Point) { 1, 0 },
};

size_t assoc_arr_get(AssocArr arr, Point point) {
  for (size_t i = 0; i < arr.size; i++) {
    Point arr_point = arr.points[i].point;
    if (arr_point.x == point.x && arr_point.y == point.y) {
      return i;
    }
  }
  if (arr.size > 1024) {
    printf("Associative Array Full!\n");
    exit(1);
  }

  arr.points[arr.size++] = {.point = point, .count = 1};
  return arr.size - 1;
}

Point point_add(Point a, Point b) {
  return (Point){
    .x = a.x + b.x,
    .y = a.y + b.y,
  };
}

int part1(char* data) {
  AssocArr arr = {0};
  arr.points[0] = (AssocArr){
    .point = (Point){ 0, 0 },
    .count = 1
  };
  arr.size = 1;
  for (char* ch = data; *ch != 0; ch++ ) {
    Point current = {0, 0};
    if (*ch == '^') {
      current = point_add(current, DELTA[0]);

    } else if (*ch == 'v') {
      current = point_add(current, DELTA[1]);
    } else if (*ch == '<') {
      current = point_add(current, DELTA[2]);
    } else if (*ch == '>') {
      current = point_add(current, DELTA[3]);
    } else {
      printf("GOT %c\n", *ch);
      exit(1);
    }
  }

  return 0;
}

int part2(char* data) {
  return 0;
}

int main(int argc, char** argv) {
  char* input_file = argv[1];
  char* data = read_to_str(input_file);

  printf("Part 1: %d\n", part1(data));
  printf("Part 2: %d\n", part2(data));
  return 0;
}


