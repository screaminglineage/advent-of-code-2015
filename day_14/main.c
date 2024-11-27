#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

#define MAX_TIME 2503
#define REINDEERS 9
// #define MAX_TIME 1000
// #define REINDEERS 2

int distance(int speed, int time_fly, int time_rest) {
    int time_left = MAX_TIME;
    int time_unit = time_fly + time_rest;

    int distance = 0;
    while (time_left > 0) {
        if (time_left - time_unit < 0 && time_fly > time_left) {
            time_fly = time_left;
        }
        distance += speed*time_fly;
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
        char name[16] = {0};
        sscanf(line, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", name, &speed, &fly, &rest);
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

int distance_step(int *time_left, int speed, int time_fly, int time_rest) {
    int time_unit = time_fly + time_rest;

    int distance = 0;
    if (*time_left - time_unit < 0 && time_fly > *time_left) {
        time_fly = *time_left;
    }
    distance += speed*time_fly;
    *time_left -= time_unit;
    return distance;
}

typedef struct {
    int speed;
    int time_fly;
    int time_rest;
} ReindeerStat;

typedef struct {
    ReindeerStat *data;
    size_t size;
    size_t capacity;
} ReindeerStats;

typedef struct {
    int distance;
    int points;
    int time_fly;
    int time_rest;
    bool flying;
} Reindeer;

typedef struct {
    Reindeer *data;
    size_t size;
    size_t capacity;
} Reindeers;

int part2(char *data) {
    ReindeerStats rs = {0};
    Reindeers rd = {0};
    char *line = strtok(data, "\n");
    while (line) {
        int speed = -1, fly = -1, rest = -1;
        char name[16] = {0};
        sscanf(line, "%s can fly %d km/s for %d seconds, but then must rest for %d seconds.", name, &speed, &fly, &rest);
        DYN_APPEND(&rs, ((ReindeerStat){speed, fly, rest}));
        DYN_APPEND(&rd, ((Reindeer){0, 0, fly, rest, true}));
        line = strtok(NULL, "\n");
    }

    int time_left = MAX_TIME;
    while (time_left > 0) {
        for (size_t i = 0; i < rd.size; i++) {
            if (rd.data[i].flying && rd.data[i].time_fly > 0) {
                rd.data[i].distance += rs.data[i].speed;
                rd.data[i].time_fly -= 1;
                if (rd.data[i].time_fly == 0) {
                    rd.data[i].flying = false;
                }

            } else if (!rd.data[i].flying && rd.data[i].time_rest > 0) {
                rd.data[i].time_rest -= 1;
                if (rd.data[i].time_rest == 0) {
                    rd.data[i].flying = true;
                    rd.data[i].time_fly = rs.data[i].time_fly;
                    rd.data[i].time_rest = rs.data[i].time_rest;
                }
            }
        }
        int max_indexes[REINDEERS] = {0};
        max_indexes[0] = rd.data[0].distance;
        int j = 0;
        for (size_t i = 0; i < rd.size; i++) {
            if (rd.data[i].distance > rd.data[max_indexes[j]].distance) {
                max_indexes[j] = i;
            } else if (rd.data[i].distance == rd.data[max_indexes[j]].distance) {
                j += 1;
                max_indexes[j] = i;
            }
        }
        for (int i = 0; i <= j; i++) {
            rd.data[max_indexes[i]].points += 1;
        }
        time_left -= 1;
    }
    /*printf("max_index = %d\n", max_index);*/
    /*printf("rd.data[max_index].distance = %d\n", rd.data[max_index].distance);*/
    // rd.data[max_index].points += 1;

    int max_index = 0;
    for (size_t i = 0; i < rd.size; i++) {
        if (rd.data[i].points > rd.data[max_index].points) {
            max_index = i;
        }
    }
    return rd.data[max_index].points;
}

int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    size_t count = 0;
    char *data = read_to_str_size(input_file, &count);

    // part1 uses strtok which destroys the original string
    char *part1_data = malloc(count);
    strcpy(part1_data, data);
    printf("Part 1: %d\n", part1(part1_data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}


