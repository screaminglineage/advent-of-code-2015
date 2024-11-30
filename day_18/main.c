#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

#define WIDTH 100
#define HEIGHT 100
#define STEPS 100
#define MAT_AT(mat, y, x) (mat)[(y) * WIDTH + (x)]

bool current[HEIGHT*WIDTH];
bool next[HEIGHT*WIDTH];

int count_neigbours(int x, int y, bool *board) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int new_x = x + dx;
            int new_y = y + dy;

            if (new_x >= 0 && new_y >= 0
                && new_x < WIDTH && new_y < HEIGHT
                && !(dx == 0 && dy == 0)
                && MAT_AT(board, new_y, new_x)) {
                count++;
            }
        }
    }
    return count;
}

void swap_pointers(bool **a, bool **b) {
    bool *tmp = *a;
    *a = *b;
    *b = tmp;
}

void game_of_life(bool *current, bool *next) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbours = count_neigbours(x, y, current);
            if (MAT_AT(current, y, x)) {
                MAT_AT(next, y, x) = (neighbours == 2 || neighbours == 3);
            } else {
                MAT_AT(next, y, x) = (neighbours == 3);
            }
        }
    }
}

void fill_current(char *data) {
    char *line = strtok(data, "\n");
    int i = 0;
    while (line) {
        for (size_t j = 0; line[j]; j++) {
            if (line[j] == '#')
                MAT_AT(current, i, j) = true;
            else
                MAT_AT(current, i, j) = false;
        }
        line = strtok(NULL, "\n");
        i++;
    }
}

int part1() {
    bool *current_p = current;
    bool *next_p = next;
    for (size_t k = 0; k < STEPS; k++) {
        game_of_life(current_p, next_p);
        swap_pointers(&current_p, &next_p);
    }

    int count = 0;
    for (size_t i = 0; i < HEIGHT*WIDTH; i++) {
        if (current_p[i]) count += 1;
    }
    return count;
}

int count_neigbours_corner(int x, int y, bool *board) {
    int count = 0;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            int new_x = x + dx;
            int new_y = y + dy;

            if ((new_x == 0 && new_y == 0)
                || (new_x == WIDTH - 1 && new_y == 0)
                || (new_x == 0 && new_y == HEIGHT - 1)
                || (new_x == WIDTH - 1 && new_y == HEIGHT - 1)
                || (new_x >= 0 && new_y >= 0
                    && new_x < WIDTH && new_y < HEIGHT
                    && !(dx == 0 && dy == 0)
                    && MAT_AT(board, new_y, new_x))) {
                count++;
            }
        }
    }
    return count;
}

void fill_corners(bool *board) {
    MAT_AT(board, 0, 0) = true;
    MAT_AT(board, HEIGHT - 1, 0) = true;
    MAT_AT(board, 0, WIDTH - 1) = true;
    MAT_AT(board, HEIGHT - 1, WIDTH - 1) = true;
}

void game_of_life2(bool *current, bool *next) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int neighbours = count_neigbours_corner(x, y, current);
            if (MAT_AT(current, y, x)) {
                MAT_AT(next, y, x) = (neighbours == 2 || neighbours == 3);
            } else {
                MAT_AT(next, y, x) = (neighbours == 3);
            }
        }
    }
    fill_corners(next);
}

int part2() {
    bool *current_p = current;
    bool *next_p = next;
    fill_corners(current_p);
    for (size_t k = 0; k < STEPS; k++) {
        game_of_life2(current_p, next_p);
        swap_pointers(&current_p, &next_p);
    }

    int count = 0;
    for (size_t i = 0; i < HEIGHT*WIDTH; i++) {
        if (current_p[i]) count += 1;
    }
    return count;
}


int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    size_t count;
    char *data = read_to_str_size(input_file, &count);

    char *copy = malloc(count + 1);
    strcpy(copy, data);
    fill_current(data);
    printf("Part 1: %d\n", part1());
    fill_current(copy);
    printf("Part 2: %d\n", part2(data));
    return 0;
}


