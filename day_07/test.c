#include <stdio.h>
#include <string.h>

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

size_t index_of(char *string, char *substr) {
    size_t string_len = strlen(string);
    size_t substr_len = strlen(substr);
    for (size_t i = 0; i <= string_len - substr_len; i++) {
        size_t j = 0;
        for (; i+j < string_len && string[i+j] == substr[j]; j++);
        if (j == substr_len) return i;
    }
    return -1;
}

char *chop_upto(char *string, char *upto) {
    size_t i = index_of(string, upto);
    if (i == -1) return string;
    return &string[i + strlen(upto)];
}

void split(char *string, char *by) {
    char *str;
    printf("%s\n", str = chop_upto(string, by));
    printf("%s\n", str = chop_upto(str, by));
}


int main() {
    char *data = "hello";
    printf("%zu\n", strcspn(data, " "));
    return  0;
}
