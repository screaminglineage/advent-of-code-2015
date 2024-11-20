#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <math.h>
#include "md5.h"
#include "../aoc.h"


#define MD5_BYTES 16

void print_md5(uint8_t hash[MD5_BYTES]) {
    for (size_t i = 0; i < MD5_BYTES; i++) {
        printf("%.2x ", hash[i]);
    }
}

bool mineable_five_zeroes(char *str, int num) {
    char buf[1024] = {0};
    snprintf(buf, 1024, "%s%d", str, num);
    uint8_t hash[MD5_BYTES] = {0};
    md5String(buf, hash);
    return hash[0] == 0 && hash[1] == 0 && (hash[2] >> 4) == 0;
}

bool mineable_six_zeroes(char *str, int num) {
    char buf[1024] = {0};
    snprintf(buf, 1024, "%s%d", str, num);
    uint8_t hash[MD5_BYTES] = {0};
    md5String(buf, hash);
    return hash[0] == 0 && hash[1] == 0 && hash[2] == 0;
}

int part1(char *data) {
    data[strcspn(data, "\n")] = 0;
    size_t i = 1;
    for (; i < SIZE_MAX; i++) {
        if (mineable_five_zeroes(data, i)) break;
    }
    return i;
}

int part2(char *data) {
    data[strcspn(data, "\n")] = 0;
    size_t i = 1;
    for (; i < SIZE_MAX; i++) {
        if (mineable_six_zeroes(data, i)) break;
    }
    return i;
}


int main(int argc, char** argv) {
    char* input_file = argv[1];
    char* data = read_to_str(input_file);

    printf("Part 1: %d\n", part1(data));
    printf("Part 2: %d\n", part2(data));
    return 0;
}

