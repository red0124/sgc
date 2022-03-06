#pragma once
#include <stdlib.h>

#define SGC_STACK_SIZE 64

#define SGC_PREPARE_STACK                                                      \
    char* stack[SGC_STACK_SIZE];                                               \
    char** stackptr = stack

#define SGC_STACK_PUSH(array, limit)                                           \
    stackptr[0] = array;                                                       \
    stackptr[1] = limit;                                                       \
    stackptr += 2

#define SGC_STACK_POP(array, limit)                                            \
    stackptr -= 2;                                                             \
    array = stackptr[0];                                                       \
    limit = stackptr[1]

#define SGC_STACK_THRESH 7
