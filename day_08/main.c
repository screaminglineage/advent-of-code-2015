#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

int actual_len(char *data) {
    int count = 0;
    for (size_t i = 0; data[i]; i++) {
        if (data[i] == '"') continue;
        if (data[i] == '\\' ) {
            if (data[i+1] && data[i+1] == 'x') {
                i += 3;
                count += 1;
            } else if (data[i+1] && (data[i+1] == '"' || data[i+1] == '\\')) {
                i += 1;
                count += 1;
            }
            continue;
        }
        count += 1;
    }
    return count;
}

int escaped_len(char *data) {
    // account for opening and closing quotes
    int count = 2;
    for (size_t i = 0; data[i]; i++) {
        if (data[i] == '"' || data[i] == '\\') {
            count += 2;
        } else {
            count += 1;
        }
    }
    return count;
}


int part1(char *data) {
    int char_count = 0;
    int actual_count = 0;
    char *line = strtok(data, "\n");
    while (line) {
        char_count += strlen(line);
        actual_count += actual_len(line);
	    line = strtok(NULL, "\n");
    }
    return char_count - actual_count;
}

int part2(char *data) {
    int char_count = 0;
    int escaped_count = 0;
    char *line = strtok(data, "\n");
    while (line) {
        char_count += strlen(line);
        escaped_count += escaped_len(line);
	    line = strtok(NULL, "\n");
    }
    return escaped_count - char_count;
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


