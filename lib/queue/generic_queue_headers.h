#pragma once
#include "generic_types.h"
#include <stdlib.h>

#define INIT_QUEUE_HEADERS(T)                                                  \
                                                                               \
        struct queue_##T                                                       \
        {                                                                      \
                size_t size;                                                   \
                size_t max;                                                    \
                size_t front;                                                  \
                size_t back;                                                   \
                T *data;                                                       \
        };                                                                     \
                                                                               \
        size_t queue_size_##T(const struct queue_##T *);                       \
        struct queue_##T queue_new_##T();                                      \
                                                                               \
        void queue_set_copy_##T(void (*copy)(T *, const T *));                 \
        void queue_set_equal_##T(int (*equal)(const T *, const T *));          \
        void queue_set_free_##T(void (*free)(T *));                            \
                                                                               \
        void queue_init_##T(struct queue_##T *);                               \
        void queue_free_##T(struct queue_##T *);                               \
        int queue_equal_##T(struct queue_##T *, struct queue_##T *);           \
                                                                               \
        void queue_copy_##T(struct queue_##T *restrict,                        \
                            const struct queue_##T *restrict);                 \
                                                                               \
        void queue_push_##T(struct queue_##T *, T);                            \
        void queue_pop_##T(struct queue_##T *);                                \
        T *queue_front_##T(const struct queue_##T *);                          \
        T *queue_back_##T(const struct queue_##T *);                           \
        int queue_empty_##T(const struct queue_##T *);
