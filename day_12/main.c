#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h> 
#include <string.h> 
#include <ctype.h>
#include "../aoc.h"

int part1(char *data) {
    int count = 0;
    while (*data) {
        char buf[16] = {0};
        char *start = data;
        if (*data == '-' && isdigit(data[1])) {
            data++;
        }
        while (*data && isdigit(*data)) data++;
        strncpy(buf, start, data - start);
        count += atoi(buf);
        data += 1;
    }
    return count;
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


