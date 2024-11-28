#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

typedef struct {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int calories;
} Ingredient;

#define AMOUNT 100
#define INGS_COUNT 4

int max_score(Ingredient ings[INGS_COUNT]) {
    int max = 0;
    for (size_t i = 0; i <= AMOUNT; i++) {
        for (size_t j = 0; i + j <= AMOUNT; j++) {
            for (size_t k = 0; i + j + k <= AMOUNT; k++) {
                for (size_t l = 0; i + j + k + l <= AMOUNT; l++) {
                    if (i + j + k + l != AMOUNT) continue;

                    int capacity = i*ings[0].capacity + j*ings[1].capacity + k*ings[2].capacity + l*ings[3].capacity;
                    int durability = i*ings[0].durability + j*ings[1].durability + k*ings[2].durability + l*ings[3].durability;
                    int flavor = i*ings[0].flavor + j*ings[1].flavor + k*ings[2].flavor + l*ings[3].flavor;
                    int texture = i*ings[0].texture + j*ings[1].texture + k*ings[2].texture + l*ings[3].texture;

                    int score = 0;
                    if (capacity > 0 && durability > 0 && flavor > 0 && texture > 0) {
                        score = capacity * durability * flavor * texture;
                    }

                    if (score > max) max = score;
                }
            }
        }
    }
    return max;
}

void parse_ingredients(char *data, Ingredient *ings) {
    int i = 0;
    char *line = strtok(data, "\n");
    while (line) {
        char name[16] = {0};
        sscanf(line, "%s capacity %d, durability %d, flavor %d, texture %d, calories %d",
               name, &ings[i].capacity, &ings[i].durability, &ings[i].flavor, &ings[i].texture, &ings[i].calories);
        line = strtok(NULL, "\n");
        i += 1;
    }
}


int part1(Ingredient ings[INGS_COUNT]) {
    return max_score(ings);
}

int max_score_calories(Ingredient ings[INGS_COUNT]) {
    int max = 0;
    for (size_t i = 0; i <= AMOUNT; i++) {
        for (size_t j = 0; i + j <= AMOUNT; j++) {
            for (size_t k = 0; i + j + k <= AMOUNT; k++) {
                for (size_t l = 0; i + j + k + l <= AMOUNT; l++) {
                    if (i + j + k + l != AMOUNT) continue;

                    int capacity = i*ings[0].capacity + j*ings[1].capacity + k*ings[2].capacity + l*ings[3].capacity;
                    int durability = i*ings[0].durability + j*ings[1].durability + k*ings[2].durability + l*ings[3].durability;
                    int flavor = i*ings[0].flavor + j*ings[1].flavor + k*ings[2].flavor + l*ings[3].flavor;
                    int texture = i*ings[0].texture + j*ings[1].texture + k*ings[2].texture + l*ings[3].texture;

                    int score = 0;
                    if (capacity > 0 && durability > 0 && flavor > 0 && texture > 0) {
                        score = capacity * durability * flavor * texture;
                    }

                    int calories = i*ings[0].calories + j*ings[1].calories + k*ings[2].calories + l*ings[3].calories;
                    if (calories == 500 && score > max) max = score;
                }
            }
        }
    }
    return max;
}

int part2(Ingredient ings[INGS_COUNT]) {
    return max_score_calories(ings);
}

int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    char *data = read_to_str(input_file);

    Ingredient ings[INGS_COUNT] = {0};
    parse_ingredients(data, ings);

    printf("Part 1: %d\n", part1(ings));
    printf("Part 2: %d\n", part2(ings));
    return 0;
}


