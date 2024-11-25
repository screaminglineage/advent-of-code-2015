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
    int count;
    bool has_red;
} Count;


typedef struct {
    Count *data;
    size_t size;
    size_t capacity;
} Stack;


typedef struct {
    char *data;
    Stack count_stack;
} State;

bool inc_state(State *state) {
    if (state->data[0] == '\0') return false;

    size_t top = state->count_stack.size - 1;

    if (state->data[0] == '{') {
        DYN_APPEND(&(state->count_stack), ((Count){0, false}));
    } else if (state->data[0] == '}') {
        if (!state->count_stack.data[top].has_red) {
            state->count_stack.data[top - 1].count += state->count_stack.data[top].count;
        }
        state->count_stack.size -= 1;
    } else if (state->data[0] == '[') {
        DYN_APPEND(&(state->count_stack), ((Count){0, false}));
    } else if (state->data[0] == ']') {
        state->count_stack.data[top - 1].count += state->count_stack.data[top].count;
        state->count_stack.size -= 1;
    } else if (starts_with(state->data, "\"red\"")) {
        state->count_stack.data[top].has_red = true;
    }
    state->data++;
    return true;
}

bool parse_num(State *state, int *num) {
    if (!isdigit(state->data[0]) && !(state->data[0] == '-' && isdigit(state->data[1]))) {
        return false;
    }

    char buf[16] = {0};
    char *start = state->data;
    if (state->data[0] == '-') state->data++;
    while (isdigit(state->data[0])) state->data++;

    strncpy(buf, start, state->data - start);
    *num = atoi(buf);
    return true;
}

int sum(Stack count_stack) {
    int sum = 0;
    for (size_t i = 0; i < count_stack.size; i++) {
        printf("count_stack.data[i].count = %d\n", count_stack.data[i].count);
        sum += count_stack.data[i].count;
    }
    return sum;
}

int part2(char *data) {
    State state = {0};
    state.data = data;
    DYN_APPEND(&(state.count_stack), ((Count){0, false}));
    while (inc_state(&state)) {
        int num = 0;
        if (parse_num(&state, &num)) {
            state.count_stack.data[state.count_stack.size - 1].count += num;
        }
    }
    return state.count_stack.data[0].count;
}


int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    char *data = read_to_str(input_file);

    printf("Part 1: %d\n", part1(data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}


