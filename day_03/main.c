#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include "../aoc.h"

typedef struct {
    int x, y;
} Point;

typedef struct {
    Point *data;
    size_t size;
    size_t capacity;
} Points;


// insert only if point doesnt exist
void dyn_update(Points *points, Point point) {
    for (size_t i = 0; i < points->size; i++) {
        Point p = points->data[i];
        if (p.x == point.x && p.y == point.y) {
            return;
        }
    }
    DYN_APPEND(points, point);
}


int part1(char *data) {
    Points points = {0};
    Point current = {0, 0};
    DYN_APPEND(&points, current);

    for (size_t i = 0; data[i]; i++) {
        Point next = current;
        switch (data[i]) {
            case '^':
                next.y += 1;
                break;
            case '>':
                next.x += 1;
                break;
            case 'v':
                next.y -= 1;
                break;
            case '<':
                next.x -= 1;
                break;
            default:
                continue;
        }
        dyn_update(&points, next);
        current = next;
    }
    return points.size;
}

int part2(char *data) {
    Points points = {0};
    Point current_santa = {0, 0};
    Point current_robo = {0, 0};
    DYN_APPEND(&points, current_santa);

    for (size_t i = 0; data[i]; i++) {
        Point next;
        if (i % 2 == 0) {
            next = current_santa;
        } else {
            next = current_robo;
        }

        switch (data[i]) {
            case '^':
                next.y += 1;
                break;
            case '>':
                next.x += 1;
                break;
            case 'v':
                next.y -= 1;
                break;
            case '<':
                next.x -= 1;
                break;
            default:
                continue;
        }
        if (i % 2 == 0) {
            current_santa = next;
        } else {
            current_robo = next;
        }
        dyn_update(&points, next);
    }
    return points.size;
}



int main(int argc, char** argv) {
    (void)argc;
    char* input_file = argv[1];
    char* data = read_to_str(input_file);

    printf("Part 1: %d\n", part1(data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}

