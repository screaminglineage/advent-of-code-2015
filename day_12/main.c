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
        while (isdigit(*data)) data++;
        strncpy(buf, start, data - start);
        count += atoi(buf);
        data += 1;
    }
    return count;
}

bool starts_with(char *string, char *prefix) {
    if (!prefix[0]) return !string[0];
    size_t i = 0;
    for (; string[i] && prefix[i]; i++) {
        if (string[i] != prefix[i]) {
            return false;
        }
    }
    return !prefix[i];
}

typedef struct {
    char *data;
    bool within_array;
    int level;
    int temp_count;
    int count;
} State;

bool inc_state(State *state) {
    if (state->data[0] == '\0') return false;

    if (state->data[0] == '[') {
        state->within_array = true;
    } else if (state->data[0] == ']') {
        state->within_array = false;
    } else if (state->data[0] == '{') {
        state->within_array = false;
        state->level += 1;
    } else if (state->data[0] == '}') {
        state->level -= 1;
        state->count += state->temp_count;
        state->temp_count = 0;
    }
    state->data++;
    return true;
}

int parse_num(State *state) {
    char buf[16] = {0};
    char *start = state->data;
    if (state->data[0] == '-' && isdigit(state->data[1])) {
        state->data++;
    }
    while (isdigit(state->data[0])) state->data++;
    strncpy(buf, start, state->data - start);
    return atoi(buf);
}

int part2(char *data) {
    State state = {0};
    state.data = data;
    while (inc_state(&state)) {
        if (starts_with(state.data, "\"red\"") && !state.within_array) {
            state.temp_count = 0;
            int current_level = state.level;
            while (inc_state(&state)) {
                if (state.level < current_level) {
                    break;
                }
            }
        }
        state.temp_count += parse_num(&state);
    }
    state.count += state.temp_count;
    return state.count;
}


int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    char *data = read_to_str(input_file);

    printf("Part 1: %d\n", part1(data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}


