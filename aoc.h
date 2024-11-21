#include <stdio.h>
#include <stdlib.h>

#define DYN_APPEND(da, item)                                                      \
do {                                                                         \
    if ((da)->size == (da)->capacity) {                                        \
        (da)->capacity = ((da)->capacity <= 0) ? 1 : (da)->capacity * 2;         \
        (da)->data = realloc((da)->data, (da)->capacity * sizeof(*(da)->data));  \
        assert((da)->data && "Catastrophic Failure: Allocation failed!");        \
    }                                                                          \
    (da)->data[(da)->size++] = item;                                           \
} while (0)


#define DYN_EXTEND(da1, da2)                        \
do {                                                \
    for(size_t i = 0; i < (da2)->size; i++) {       \
        DYN_APPEND((da1), (da2)->data[i]);          \
    }                                               \
} while(0)


#define MIN_ELEM(arr, count) ({ \
  typeof((arr[0])) __min = (arr[0]); \
  do { \
    for (size_t i = 0; i<(count); i++) { \
      if ((arr[i]) < __min) { \
        __min = (arr[i]); \
      } \
    } \
  } while (0); \
  __min; \
}) \

#define ARR_LEN(arr) (sizeof((arr))/sizeof((arr[0])))

char *read_to_str(char* filepath) {
    FILE* file = fopen(filepath, "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* data = malloc(size + 1);
    fread(data, size, 1, file);
    fclose(file);

    data[size] = 0;
    return data;
}

char *read_to_str_size(char* filepath, size_t *size_out) {
    FILE* file = fopen(filepath, "r");
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* data = malloc(size + 1);
    fread(data, size, 1, file);
    fclose(file);

    data[size] = 0;
    *size_out = size + 1;
    return data;
}





