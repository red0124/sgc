#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_PRIORITY_QUEUE_TYPE_FUNCTIONS(T, N)                          \
    static void N##_stack_size(T* i, T* j) {                                   \
        char* tmp[sizeof(T)];                                                  \
                                                                               \
        memcpy(tmp, i, sizeof(T));                                             \
        memcpy(i, j, sizeof(T));                                               \
        memcpy(j, tmp, sizeof(T));                                             \
    }                                                                          \
                                                                               \
    static void N##_is_left_child(struct N* p) {                               \
        size_t curr = p->size_;                                                \
        while (curr > 0) {                                                     \
            size_t parent = (curr - 1) >> 1;                                   \
            T* parent_data = &p->data_[parent];                                \
            T* curr_data = &p->data_[curr];                                    \
            if (T##_compare(parent_data, curr_data) < 0) {                     \
                N##_stack_size(parent_data, curr_data);                        \
                curr = parent;                                                 \
            } else {                                                           \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push(struct N* p, T el) {                                         \
        N##_node(p);                                                           \
        SGC_COPY(T##_copy, p->data_[p->size_], el, p->shared_);                \
        N##_is_left_child(p);                                                  \
        ++p->size_;                                                            \
    }                                                                          \
                                                                               \
    static void N##_resize(struct N* p) {                                      \
        size_t curr = 0;                                                       \
        while ((curr + 1) * 2 <= p->size_) {                                   \
            size_t right = (curr + 1) * 2;                                     \
            size_t left = right - 1;                                           \
            size_t tmp = right;                                                \
            if (right == p->size_ ||                                           \
                T##_compare(&p->data_[left], &p->data_[right]) > 0) {          \
                tmp = left;                                                    \
            }                                                                  \
            if (T##_compare(&p->data_[tmp], &p->data_[curr]) > 0) {            \
                N##_stack_size(&p->data_[curr], &p->data_[tmp]);               \
                curr = tmp;                                                    \
            } else {                                                           \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop(struct N* p) {                                                \
        if (p->size_) {                                                        \
            N##_stack_size(&p->data_[0], &p->data_[--p->size_]);               \
            if (!p->shared_) {                                                 \
                T##_free(&p->data_[p->size_]);                                 \
            }                                                                  \
            N##_resize(p);                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    const T* N##_top(const struct N* const p) {                                \
        if (p->size_) {                                                        \
            return &p->data_[0];                                               \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    T* N##_array(struct N* d) {                                                \
        T* ret = NULL;                                                         \
        if (d->size_) {                                                        \
            ret = d->data_;                                                    \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_from_array(struct N* p, const T* const arr, const size_t size) {  \
        N##_init(p);                                                           \
        if (size) {                                                            \
            for (size_t i = 0; i < size; ++i) {                                \
                N##_push(p, arr[i]);                                           \
            }                                                                  \
        } else {                                                               \
            p->size_ = 0;                                                      \
        }                                                                      \
    }