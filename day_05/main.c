#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

bool is_vowel(char ch) {
    switch (ch) {
        case 'a':
        case 'e':
        case 'i':
        case 'o':
        case 'u':
            return true;
        default:
            return false;
    }
}

bool letters_match(char *string) {
    bool doubles = false;
    int vowels_count = 0;
    size_t i = 0;
    for (; string[i] && string[i+1]; i++) {
        if (string[i] == 'a' && string[i+1] == 'b'
            || string[i] == 'c' && string[i+1] == 'd'
            || string[i] == 'p' && string[i+1] == 'q'
            || string[i] == 'x' && string[i+1] == 'y') {
            return false;
        }

        if (string[i] == string[i+1]) {
            doubles = true;
        }

        if (is_vowel(string[i])) {
            vowels_count++;
        }
    }
    if (is_vowel(string[i])) {
        vowels_count++;
    }
    return doubles && vowels_count >= 3;
}

int part1(char *data) {
    char *line = strtok(data, "\n");
    int nice_strings = 0;
    while (line) {
        if (letters_match(line)) {
            nice_strings += 1;
        }
	    line = strtok(NULL, "\n");
    }

    return nice_strings;
}

bool letters_match_2(char *string) {
    bool doubles_with_gap = false;
    bool matching_pairs = false;
    for (size_t i = 0; string[i] && string[i+1] && string[i+2]; i++) {
        if (string[i] == string[i+2]) {
            doubles_with_gap = true;
        }
        for (size_t j = i+2; string[j] && string[j+1]; j++) {
            if (string[i] == string[j] && string[i+1] == string[j+1]) {
                matching_pairs = true;
            }
        }
    }
    return doubles_with_gap && matching_pairs;
}

int part2(char *data) {
    char *line = strtok(data, "\n");
    int nice_strings = 0;
    while (line) {
        if (letters_match_2(line)) {
            nice_strings += 1;
        }
	    line = strtok(NULL, "\n");
    }

    return nice_strings;
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


