#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

#define MAX_TIME 2503
#define REINDEERS 9

int distance(int speed, int time_fly, int time_rest) {
    int time_left = MAX_TIME;
    int time_unit = time_fly + time_rest;

    int distance = 0;
    while (time_left > 0) {

        if (time_left - time_unit < 0) {
            if (time_fly <= time_left) {
                distance += speed*time_fly;
            } else {
                distance += speed*time_left;
            }
            break;
        } else {
            distance += speed*time_fly;
        }

        time_left -= time_unit;
    }
    return distance;
}


int part1(char *data) {
    int distances[REINDEERS];
    int i = 0;
    char *line = strtok(data, "\n");
    while (line) {
        int speed = -1, fly = -1, rest = -1;
        char tmp[32] = {0};
        sscanf(line, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", tmp, &speed, &fly, &rest);
        distances[i++] = distance(speed, fly, rest);
	    line = strtok(NULL, "\n");
    }

    int max = distances[0];
    for (size_t i = 0; i < REINDEERS; i++) {
        if (distances[i] > max) {
            max = distances[i];
        }
    }
    return max;
}

int part2(char *data) {
    return 0;
}

int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    size_t count = 0;
    char *data = read_to_str_size(input_file, &count);

    // part1 uses strtok which destroys the original string
    char *part1_data = malloc(count);
    strcpy(part1_data, data);
    printf("Part 1: %d\n", part1(data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}


