#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

#define WIDTH 999
#define HEIGHT 999

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


int count_lights(bool *lights) {
    int count = 0;
    for (size_t i = 0; i < WIDTH*HEIGHT; i++) {
        if (lights[i]) count += 1;
    }
    return count;
}

int set_lights_1(RectActions actions, bool *lights) {
    for (size_t i = 0; i < actions.size; i++) {
        RectAction action = actions.data[i];

        for (int y = action.y1; y <= action.y2; y++) {
            for (int x = action.x1; x <= action.x2; x++) {
                switch (action.action) {
                    case TOGGLE:
                        lights[y*WIDTH + x] = !lights[y*WIDTH + x];
                        break;
                    case TURN_ON:
                        lights[y*WIDTH + x] = true;
                        break;
                    case TURN_OFF:
                        lights[y*WIDTH + x] = false;
                        break;
                    default:
                        printf("Unreachable: %d\n", action.action);
                        exit(1);
                }
            }
        }
    }
    return count_lights(lights);
}


int part1(char *data) {
    bool lights[WIDTH*HEIGHT] = {0};
    char *line = strtok(data, "\n");
    RectActions actions = {0};
    while (line) {
        DYN_APPEND(&actions, parse_line(line));
	    line = strtok(NULL, "\n");
    }
    return set_lights_1(actions, lights);
}


int count_brightness(int *lights) {
    int count = 0;
    for (size_t i = 0; i < WIDTH*HEIGHT; i++) {
        count += lights[i];
    }
    return count;
}

int set_lights_2(RectActions actions, int *lights) {
    for (size_t i = 0; i < actions.size; i++) {
        RectAction action = actions.data[i];

        for (int y = action.y1; y <= action.y2; y++) {
            for (int x = action.x1; x <= action.x2; x++) {
                switch (action.action) {
                    case TOGGLE:
                        lights[y*WIDTH + x] += 2;
                        break;
                    case TURN_ON:
                        lights[y*WIDTH + x] += 1;
                        break;
                    case TURN_OFF:
                        if (lights[y*WIDTH + x] > 0) lights[y*WIDTH + x] -= 1;
                        break;
                    default:
                        printf("Unreachable: %d\n", action.action);
                        exit(1);
                }
            }
        }
    }
    return count_brightness(lights);
}


int part2(char *data) {
    int lights[WIDTH*HEIGHT] = {0};
    char *line = strtok(data, "\n");
    RectActions actions = {0};
    while (line) {
        DYN_APPEND(&actions, parse_line(line));
	    line = strtok(NULL, "\n");
    }
    return set_lights_2(actions, lights);
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


