#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

#define WIDTH 999
#define HEIGHT 999
bool arr[WIDTH*HEIGHT] = {0};

typedef enum {
    TOGGLE,
    TURN_ON,
    TURN_OFF
} Action;

typedef struct {
    int x1, y1, x2, y2;
    Action action;
} RectAction;

typedef struct {
    RectAction *data;
    size_t size;
    size_t capacity;
} RectActions;


int count_lights() {
    int count = 0;
    for (size_t i = 0; i < WIDTH*HEIGHT; i++) {
        if (arr[i]) count += 1;
    }
    return count;
}

int set_lights(RectActions actions) {
    for (size_t i = 0; i < actions.size; i++) {
        RectAction action = actions.data[i];

        for (size_t y = action.y1; y <= action.y2; y++) {
            for (size_t x = action.x1; x <= action.x2; x++) {
                switch (action.action) {
                    case TOGGLE:
                        arr[y*WIDTH + x] = !arr[y*WIDTH + x];
                        break;
                    case TURN_ON:
                        arr[y*WIDTH + x] = true;
                        break;
                    case TURN_OFF:
                        arr[y*WIDTH + x] = false;
                        break;
                    default:
                        printf("Unreachable: %d\n", action.action);
                        exit(1);
                }
            }
        }
    }
    return count_lights();
}


bool starts_with(char *string, char *prefix, size_t *index) {
    if (!prefix[0]) return !string[0];
    size_t i = 0;
    for (; string[i] && prefix[i]; i++) {
        if (string[i] != prefix[i]) {
            return false;
        }
    }
    if (index) *index = i;
    return !prefix[i];
}


RectAction parse_line(char *line) {
    size_t i = 0;
    RectAction r;
    int x1, y1, x2, y2;
    if (starts_with(line, "toggle ", &i)) {
        sscanf(&line[i], "%d,%d through %d,%d", &x1, &y1, &x2, &y2);
        r = (RectAction){x1, y1, x2, y2, TOGGLE};
    } else if (starts_with(line, "turn off ", &i)) {
        sscanf(&line[i], "%d,%d through %d,%d", &x1, &y1, &x2, &y2);
        r = (RectAction){x1, y1, x2, y2, TURN_OFF};
    } else if (starts_with(line, "turn on ", &i)) {
        sscanf(&line[i], "%d,%d through %d,%d", &x1, &y1, &x2, &y2);
        r = (RectAction){x1, y1, x2, y2, TURN_ON};
    } else {
        printf("Unreachable!: %s\n", line);
        exit(1);
    }
    return r;
}

int part1(char *data) {
    char *line = strtok(data, "\n");
    RectActions actions = {0};
    while (line) {
        DYN_APPEND(&actions, parse_line(line));
	    line = strtok(NULL, "\n");
    }
    return set_lights(actions);
}

int part2(char *data) {
    return 0;
}


int main(int argc, char** argv) {
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


