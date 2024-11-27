#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

int distance(int speed, int time_fly, int time_rest) {
    int time_left = 1000;
    int time_unit = time_fly + time_rest;

    int distance = 0;
    while (time_left > 0) {
        printf("time_left = %d\n", time_left);

        if (time_left - time_unit < 0) {
            if (time_fly <= time_left) {
                distance += speed*time_fly;
            } else {
                distance += speed*time_left;
            }
            printf("distance = %d\n", distance);
            break;
        } else {
            distance += speed*time_fly;
            printf("distance = %d\n", distance);
        }

        time_left -= time_unit;
    }
    return distance;
}


int part1(char *data) {
    printf("%s\n", data);
    return 0;
}

int part2(char *data) {
    return 0;
}

int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    char *data = read_to_str(input_file);

    printf("Part 1: %d\n", part1(data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}


