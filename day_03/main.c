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

bool contains(Points points, Point p) {
    for (size_t i = 0; i < points.size; i++) {
        Point p1 = points.data[i];
        if (p1.x == p.x && p1.y == p.y) {
            return true;
        }
    }
    return false;
}

int count_unique_points(Points points) {
    Points unique_points = {0};
    for (size_t i = 0; i < points.size; i++) {
        Point p1 = points.data[i];
        if (contains(unique_points, p1)) {
            continue;
        }
        DYN_APPEND(&unique_points, p1);
    }
    return unique_points.size;
}

int part1(char *data) {
    Points points = {0};
    Point start = {0, 0};
    DYN_APPEND(&points, start);

    for (size_t i = 0; data[i]; i++) {
        Point next = {points.data[points.size - 1].x, points.data[points.size - 1].y};
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
        DYN_APPEND(&points, next);
    }
    return count_unique_points(points);
}

int part2(char *data) {
    Points points_santa = {0};
    Points points_robo = {0};
    Point start = {0, 0};
    DYN_APPEND(&points_santa, start);
    DYN_APPEND(&points_robo, start);

    for (size_t i = 0; data[i]; i++) {
        Point next; 
        if (i % 2 == 0) {
            next = (Point){points_santa.data[points_santa.size - 1].x, points_santa.data[points_santa.size - 1].y};
        } else {
            next = (Point){points_robo.data[points_robo.size - 1].x, points_robo.data[points_robo.size - 1].y};
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
            DYN_APPEND(&points_santa, next);
        } else {
            DYN_APPEND(&points_robo, next);
        }
    }
    DYN_EXTEND(&points_santa, &points_robo);
    return count_unique_points(points_santa);
}



int main(int argc, char** argv) {
    char* input_file = argv[1];
    char* data = read_to_str(input_file);

    printf("Part 1: %d\n", part1(data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}

