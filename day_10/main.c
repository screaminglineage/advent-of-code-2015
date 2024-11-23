#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

size_t look_and_say(char *current, char *next, int iterations) {
    for (int i = 0; i < iterations; i++) {
        char ch = current[0];
        int count = 0;
        char *old_next = next;
        for (size_t j = 0; current[j]; j++) {
            if (ch != current[j]) {
                int skip = sprintf(next, "%d%c", count, ch);
                next += skip;
                count = 0;
                ch = current[j];
            }
            count += 1;
        }
        sprintf(next, "%d%c", count, ch);
        next = old_next;

        char *tmp = next;
        next = current;
        current = tmp;
    }
    return strlen(current);
}


int part1(char *data) {
    // allocate a ridiculous amount of space to solve it in the dumbest way
    char a[1024*1024] = {0};
    char b[1024*1024] = {0};

    char *current = a, *next = b;
    strcpy(current, data);
    return look_and_say(current, next, 40);
}

int part2(char *data) {
    // allocate a ridiculous amount of space to solve it in the dumbest way
    char *a = calloc(1024*1024*4, sizeof(char));
    char *b = calloc(1024*1024*4, sizeof(char));

    char *current = a, *next = b;
    strcpy(current, data);
    return look_and_say(current, next, 50);
}

int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    char *data = read_to_str(input_file);
    data[strcspn(data, "\n")] = 0;

    printf("Part 1: %d\n", part1(data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}


