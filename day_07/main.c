#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "../aoc.h"

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} Strings;

typedef enum {
    NUM,
    VAR
} InputKind;

typedef enum {
    SET,
    NOT,
    AND,
    OR,
    LSHIFT,
    RSHIFT
} Operator;

typedef struct {
    InputKind kind;
    union {
        int num;
        char *var;
    };
} Input;

typedef struct {
    Input input[2];
    Operator op;
    char *output;
} Logic;

typedef struct {
    Logic *data;
    size_t size;
    size_t capacity;
} Logics;


void print_logic(Logic logic) {
    size_t count = (logic.op == NOT || logic.op == SET)? 1: 2;
    for (size_t i = 0; i < count; i++) {
        Input input = logic.input[i];
        if (input.kind == NUM) {
            printf("in: %d\n", input.num);
        } else {
            printf("in: %s\n", input.var);
        }
    }
    switch(logic.op) {
        case SET:
            printf("op: SET\n"); break;
        case NOT:
            printf("op: NOT\n"); break;
        case AND:
            printf("op: AND\n"); break;
        case OR:
            printf("op: OR\n"); break;
        case LSHIFT:
            printf("op: LSHIFT\n"); break;
        case RSHIFT:
            printf("op: RSHIFT\n"); break;
    }

    printf("out: %s\n", logic.output);
}

void set_logic_input(char *string, Logic *logic, size_t num) {
    if (isdigit(string[0])) {
        logic->input[num].kind = NUM;
        logic->input[num].num = atoi(string);
    } else {
        logic->input[num].kind = VAR;
        logic->input[num].var = string;
    }
}

void set_logic_binop(char *string, Logic *logic) {
    if (strcmp(string, "AND") == 0) {
        logic->op = AND;
    } else if (strcmp(string, "OR") == 0) {
        logic->op = OR;
    } else if (strcmp(string, "LSHIFT") == 0) {
        logic->op = LSHIFT;
    } else if (strcmp(string, "RSHIFT") == 0) {
        logic->op = RSHIFT;
    }
}

Logic parse_line(char *string) {
    char *line[5] = {0};
    size_t j = 0;
    while (*string) {
        size_t i = strcspn(string, " ");
        if (!string[i]) {
            line[j++] = string;
            break;
        }
        string[i] = '\0';
        line[j++] = string;
        string = &string[i+1];
    }

    Logic logic = {0};
    // set operation (123 -> z)
    if (j == 3) {
        set_logic_input(line[0], &logic, 0);
        logic.op = SET;
        logic.output = line[2];
        return logic;
    }

    // NOT operation
    if (j == 4) {
        set_logic_input(line[1], &logic, 0);
        logic.op = NOT;
        logic.output = line[3];
        return logic;
    }

    assert(j == 5);
    set_logic_input(line[0], &logic, 0);
    set_logic_input(line[2], &logic, 1);
    set_logic_binop(line[1], &logic);
    logic.output = line[4];
    return logic;
}

typedef struct {
    char *name;
    uint16_t value;
} Variable;

typedef struct {
    Variable *data;
    size_t size;
    size_t capacity;
} Variables;

// insert only if var doesnt exist
size_t var_get(Variables vars, char *var) {
    for (size_t i = 0; i < vars.size; i++) {
        Variable v = vars.data[i];
        if (strcmp(v.name, var) == 0) {
            return i;
        }
    }
    return -1;
}


void emulate(Logics program, Variables *vars) {
    for (size_t i = 0; i < program.size; i++) {
        Logic logic = program.data[i];
        if (logic.input[0].kind != NUM && logic.input[1].kind != NUM) {
            size_t b_index = var_get(*vars, logic.input[0]);
            size_t a_index = var_get(*vars, logic.input[1]);
            if (a_index == -1) {
                DYN_APPEND(&stack, logic.input[0].);
                DYN_APPEND(&stack, logic);
            }
        }


        //     switch (logic.op) {
        //         case SET: {
        //             if (logic.input[0].kind == NUM) {
        //                 vars->data[out_index].value = logic.input[0].num;
        //             } else {
        //                 size_t in_index = var_get(*vars, logic.input[0].var);
        //                 vars->data[out_index].value = vars->data[in_index].value;
        //             }
        //         } break;
        //         case NOT: {
        //             if (logic.input[0].kind == NUM) {
        //                 vars->data[out_index].value = ~logic.input[0].num;
        //             } else {
        //                 size_t in_index = var_get(*vars, logic.input[0].var);
        //                 vars->data[out_index].value = ~vars->data[in_index].value;
        //             }
        //         } break;
        //         case AND:
        //         case OR:
        //         case LSHIFT:
        //         case RSHIFT:
        //             assert(false && "TODO!");
        //     }
        // }
    }


    int part1(char *data) {
#define str "123 -> q\nNOT q -> z"
        size_t size = strlen(str);
        data = malloc(size + 1);
        memcpy(data, (char[]){str}, size + 1);

        Logics program = {0};
        char *line = strtok(data, "\n");
        while (line) {
            Logic l = parse_line(line);
            DYN_APPEND(&program, l);
            line = strtok(NULL, "\n");
        }

        Variables vars = {0};
        emulate(program, &vars);
        printf("%d\n", vars.data[var_get(&vars, "z")].value);
        return 0;
    }

    int part2(char *data) {
        return 0;
    }


    int main(int argc, char** argv) {
        (void)argc;
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


