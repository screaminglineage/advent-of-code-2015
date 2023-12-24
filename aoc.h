#include <stdio.h>
#include <stdlib.h>

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

char* read_to_str(char* filepath) {
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




