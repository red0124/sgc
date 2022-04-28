#pragma once
#include <stdbool.h>
#include <stdlib.h>

#define _SGC_INIT_COMMON_PRIORITY_QUEUE(T, N)                                  \
    static void _p_##N##_swap(T* i, T* j) {                                    \
        char* tmp[sizeof(T)];                                                  \
                                                                               \
        memcpy(tmp, i, sizeof(T));                                             \
        memcpy(i, j, sizeof(T));                                               \
        memcpy(j, tmp, sizeof(T));                                             \
    }                                                                          \
                                                                               \
    static void _p_##N##_fix_insert(N* p) {                                    \
        size_t curr = p->size_;                                                \
        while (curr > 0) {                                                     \
            size_t parent = (curr - 1) / 2;                                    \
            T* parent_data = &p->data_[parent];                                \
            T* curr_data = &p->data_[curr];                                    \
            if (T##_compare(parent_data, curr_data) < 0) {                     \
                _p_##N##_swap(parent_data, curr_data);                         \
                curr = parent;                                                 \
            } else {                                                           \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push(N* p, T el) {                                                \
        if (!_p_##N##_resize(p)) {                                             \
            return;                                                            \
        }                                                                      \
        _SGC_COPY(T, p->data_[p->size_], el, p->sharing_);                     \
        _p_##N##_fix_insert(p);                                                \
        ++p->size_;                                                            \
    }                                                                          \
                                                                               \
    static void _p_##N##_fix_erase(N* p) {                                     \
        size_t curr = 0;                                                       \
        while ((curr + 1) * 2 - 1 < p->size_) {                                \
            size_t right = (curr + 1) * 2;                                     \
            size_t left = right - 1;                                           \
            size_t tmp = right;                                                \
            if (right == p->size_ ||                                           \
                T##_compare(&p->data_[left], &p->data_[right]) > 0) {          \
                tmp = left;                                                    \
            }                                                                  \
            if (T##_compare(&p->data_[tmp], &p->data_[curr]) > 0) {            \
                _p_##N##_swap(&p->data_[curr], &p->data_[tmp]);                \
                curr = tmp;                                                    \
            } else {                                                           \
                break;                                                         \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_pop(N* p) {                                                       \
        if (p->size_) {                                                        \
            _p_##N##_swap(&p->data_[0], &p->data_[--p->size_]);                \
            _SGC_FREE(T, p->data_[p->size_], p->sharing_)                      \
            _p_##N##_fix_erase(p);                                             \
        }                                                                      \
    }                                                                          \
                                                                               \
    const T* N##_top(const N* const p) {                                       \
        if (p->size_) {                                                        \
            return &p->data_[0];                                               \
        }                                                                      \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_from_array(N* p, const T* const arr, size_t size) {               \
        N##_init(p);                                                           \
        if (size) {                                                            \
            for (size_t i = 0; i < size; ++i) {                                \
                N##_push(p, arr[i]);                                           \
            }                                                                  \
        }                                                                      \
    }
