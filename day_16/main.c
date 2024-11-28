#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

typedef struct {
    int children;
    int cats;
    int samoyeds;
    int pomeranians;
    int akitas;
    int vizslas;
    int goldfish;
    int trees;
    int cars;
    int perfumes;
} AuntSue;

#define AUNT_COUNT 500
#define FEATURE_COUNT 3

void assign_feature(char *feature, int count, AuntSue *sue) {
    if (strcmp(feature, "children:") == 0) {
        sue->children = count;
    } else if (strcmp(feature, "cats:") == 0) {
        sue->cats = count;
    } else if (strcmp(feature, "samoyeds:") == 0) {
        sue->samoyeds = count;
    } else if (strcmp(feature, "pomeranians:") == 0) {
        sue->pomeranians = count;
    } else if (strcmp(feature, "akitas:") == 0) {
        sue->akitas = count;
    } else if (strcmp(feature, "vizslas:") == 0) {
        sue->vizslas = count;
    } else if (strcmp(feature, "goldfish:") == 0) {
        sue->goldfish = count;
    } else if (strcmp(feature, "trees:") == 0) {
        sue->trees = count;
    } else if (strcmp(feature, "cars:") == 0) {
        sue->cars = count;
    } else if (strcmp(feature, "perfumes:") == 0) {
        sue->perfumes = count;
    } else {
        printf("Unreachable! Got %s\n", feature);
        exit(1);
    }
}


void parse_data(char *data, AuntSue sues[AUNT_COUNT]) {
    int i = 0;
    char *line = strtok(data, "\n");
    while (line) {
        int ignore;
        char features[FEATURE_COUNT][16] = {0};
        int counts[FEATURE_COUNT] = {0};
        sscanf(line, "Sue %d: %s %d, %s %d, %s %d",
               &ignore, features[0], &counts[0], features[1], &counts[1], features[2], &counts[2]);

        for (size_t j = 0; j < FEATURE_COUNT; j++) {
            assign_feature(features[j], counts[j], &sues[i]);
        }

        line = strtok(NULL, "\n");
        i += 1;
    }
}


int part1(AuntSue sues[AUNT_COUNT], AuntSue my_sue) {
    for (size_t i = 0; i < AUNT_COUNT; i++) {
        int count = 0;
        if (my_sue.children == sues[i].children) count++;
        if (my_sue.cats == sues[i].cats) count++;
        if (my_sue.samoyeds == sues[i].samoyeds) count++;
        if (my_sue.pomeranians == sues[i].pomeranians) count++;
        if (my_sue.akitas == sues[i].akitas) count++;
        if (my_sue.vizslas == sues[i].vizslas) count++;
        if (my_sue.goldfish == sues[i].goldfish) count++;
        if (my_sue.trees == sues[i].trees) count++;
        if (my_sue.cars == sues[i].cars) count++;
        if (my_sue.perfumes == sues[i].perfumes) count++;

        if (count == FEATURE_COUNT) return i + 1;
    }
    printf("Unreachable! Problem must have a solution\n");
    exit(1);
}

int part2(AuntSue sues[AUNT_COUNT], AuntSue my_sue) {
    for (size_t i = 0; i < AUNT_COUNT; i++) {
        int count = 0;
        if (my_sue.children == sues[i].children) count++;
        if (sues[i].cats != -1 && my_sue.cats < sues[i].cats) count++;
        if (my_sue.samoyeds == sues[i].samoyeds) count++;
        if (sues[i].pomeranians != -1 && my_sue.pomeranians > sues[i].pomeranians) count++;
        if (my_sue.akitas == sues[i].akitas) count++;
        if (my_sue.vizslas == sues[i].vizslas) count++;
        if (sues[i].goldfish != -1 && my_sue.goldfish > sues[i].goldfish) count++;
        if (sues[i].trees != -1 && my_sue.trees < sues[i].trees) count++;
        if (my_sue.cars == sues[i].cars) count++;
        if (my_sue.perfumes == sues[i].perfumes) count++;

        if (count == FEATURE_COUNT) return i + 1;
    }
    printf("Unreachable! Problem must have a solution\n");
    exit(1);
}

int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    char *data = read_to_str(input_file);

    AuntSue sues[AUNT_COUNT];
    memset(sues, -1, AUNT_COUNT*sizeof(*sues));
    parse_data(data, sues);

    AuntSue aunt_to_find = {
        3, 7, 2, 3, 0, 0, 5, 3, 2, 1,
    };

    printf("Part 1: %d\n", part1(sues, aunt_to_find));
    printf("Part 2: %d\n", part2(sues, aunt_to_find));
    return 0;
}


