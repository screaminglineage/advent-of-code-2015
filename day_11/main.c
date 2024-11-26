#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "../aoc.h"

const char *alphabet = "abcdefghijklmnopqrstuvwxyz";

void rev(char *next, const char *tmp, size_t len) {
    for (size_t i = 0; i < len; i++) {
        next[i] = tmp[len - i - 1];
    }
}

void increment_password(const char *password, char *next) {
    long num = 0;
    for (size_t i = 0; password[i]; i++) {
        for (size_t j = 0; j < 26; j++) {
            if (alphabet[j] == password[i]) {
                num = num*26 + (j+1);
                break;
            }
        }
    }
    num += 1;
    char tmp[9] = {0};
    int j = 0;
    while (num > 0) {
        num -= 1;
        tmp[j++] = alphabet[num % 26];
        num /= 26;
    }
    rev(next, tmp, j);
}

bool password_check(const char *password) {
    bool increasing_run = false;
    bool excluded = true;
    int pairs_index = -1;
    int pairs = 0;
    for (size_t i = 0; password[i]; i++) {
        if (password[i] == 'i' || password[i] == 'l' || password[i] == 'o') {
            return false;
        }
        if (password[i + 1]
            && password[i + 2]
            && (password[i + 1] - password[i] == 1)
            && (password[i + 2] - password[i + 1] == 1)) {
            increasing_run = true;
        }
        if (i != pairs_index + 1 && password[i+1] && password[i] == password[i+1]) {
            pairs += 1;
            pairs_index = i;
        }
    }
    /*printf("increasing_run = %d\n", increasing_run);*/
    /*printf("excluded = %d\n", excluded);*/
    /*printf("pairs = %d\n", pairs >= 2);*/
    return increasing_run && excluded && pairs >= 2;
}


void part1(char *data) {
    char current[9] = {0};
    char next[9] = {0};
    strcpy(current, data);
    while (!password_check(current)) {
        increment_password(current, next);
        strcpy(current, next);
    }
    printf("Part 1: %s\n", current);
}

int part2(char *data) {
    char current[9] = {0};
    char next[9] = {0};
    strcpy(current, data);
    while (!password_check(current)) {
        increment_password(current, next);
        strcpy(current, next);
    }
    increment_password(current, next);
    strcpy(current, next);
    while (!password_check(current)) {
        increment_password(current, next);
        strcpy(current, next);
    }
    printf("Part 2: %s\n", current);
}

int main(int argc, char** argv) {
    (void)argc;
    char *input_file = argv[1];
    char *data = read_to_str(input_file);
    data[strcspn(data, "\n")] = 0;

    part1(data);
    part2(data);
    return 0;
}


