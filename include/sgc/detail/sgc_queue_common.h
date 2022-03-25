#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_QUEUE_TYPE_FUNCTIONS(T, N)                                   \
    static void N##_move(size_t* flag, size_t max) {                           \
        if ((++*flag) == max) {                                                \
            *flag = 0;                                                         \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push(struct N* q, T el) {                                         \
        N##_resize(q);                                                         \
        if (!N##_empty(q)) {                                                   \
            N##_move(&q->back_, N##_max(q));                                   \
        }                                                                      \
        SGC_COPY(T##_copy, q->data_[q->back_], el, q->shared_);                \
        ++q->size_;                                                            \
    }                                                                          \
                                                                               \
    T* N##_front(struct N* q) {                                                \
        if (N##_empty(q)) {                                                    \
            return NULL;                                                       \
        }                                                                      \
        return &q->data_[q->front_];                                           \
    }                                                                          \
                                                                               \
    void N##_set_front(struct N* q, T new_el) {                                \
        if (q->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, q->data_[q->front_], new_el,       \
                        q->shared_);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_back(struct N* q) {                                                 \
        T* ret = NULL;                                                         \
        if (q->size_) {                                                        \
            ret = &q->data_[q->back_];                                         \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* q, T new_el) {                                 \
        if (q->size_ > 0) {                                                    \
            SGC_REPLACE(T##_copy, T##_free, q->data_[q->back_], new_el,        \
                        q->shared_);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop(struct N* q) {                                                \
        if (q->size_) {                                                        \
            SGC_FREE(T##_free, q->data_[q->front_], q->shared_);               \
            --q->size_;                                                        \
            if (q->size_ > 0) {                                                \
                N##_move(&q->front_, N##_max(q));                              \
            }                                                                  \
        }                                                                      \
    }
