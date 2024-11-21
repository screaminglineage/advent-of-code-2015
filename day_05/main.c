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
    for (size_t i = 0; string[i] && string[i+1] && string[i+2]; i++) {
        if (string[i] == string[i+2]) {
            return true;
        }
    }
}

bool pair_appears_twice(char *string) {
    for (size_t i = 0; string[i] && string[i+1]; i++) {
        // search for identical pair to string[i], string[i+1]
        for (size_t j = i+2; string[j] && string[j+1]; j++) {
            if (string[i] == string[j] && string[i+1] == string[j+1]) {
                return true;
            }
        }
    }
    return false;
}

int part2(char *data) {
    char *line = strtok(data, "\n");
    int nice_strings = 0;
    while (line) {
        if (letters_match_2(line) && pair_appears_twice(line)) {
            nice_strings += 1;
        }
	    line = strtok(NULL, "\n");
    }

    return nice_strings;
}


int main(int argc, char** argv) {
    char* input_file = argv[1];
    char* data = read_to_str(input_file);

    // printf("Part 1: %d\n", part1(data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}


