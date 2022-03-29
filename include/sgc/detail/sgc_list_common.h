#pragma once
#include <stdlib.h>

#define _SGC_INIT_COMMON_LIST_TYPE_FUNCTIONS(T, N)                             \
    static struct N##_node* _p_##N##_node_alloc(struct N* l) {                 \
        (void)l;                                                               \
        struct N##_node* ret =                                                 \
            (struct N##_node*)sgc_malloc(sizeof(struct N##_node));             \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    static void _p_##N##_node_free(struct N* l, struct N##_node* n) {          \
        (void)l;                                                               \
        free(n);                                                               \
    }                                                                          \
                                                                               \
    static void _p_##N##_memswp(char* i, char* j) {                            \
        char tmp[sizeof(struct N##_node*)];                                    \
                                                                               \
        memcpy(tmp, i, sizeof(struct N##_node*));                              \
        memcpy(i, j, sizeof(struct N##_node*));                                \
        memcpy(j, tmp, sizeof(struct N##_node*));                              \
    }                                                                          \
                                                                               \
    static inline bool _p_##_p_##N##_node_compare(const void* first,           \
                                                  const void* second,          \
                                                  int comp(const void*,        \
                                                           const void*)) {     \
        struct N##_node* first_ = *(struct N##_node**)first;                   \
        struct N##_node* second_ = *(struct N##_node**)second;                 \
        return comp(&first_->data_, &second_->data_);                          \
    }                                                                          \
                                                                               \
    static void _p_##N##_qsort(void* array, size_t array_size,                 \
                               int (*comp)(const void*, const void*)) {        \
        char *i, *j;                                                           \
        size_t thresh = SGC_STACK_THRESH * sizeof(struct N##_node*);           \
        char* array_ = (char*)array;                                           \
        char* limit = array_ + array_size * sizeof(struct N##_node*);          \
        SGC_PREPARE_STACK;                                                     \
                                                                               \
        while (1) {                                                            \
            if ((size_t)(limit - array_) > thresh) {                           \
                i = array_ + sizeof(struct N##_node*);                         \
                j = limit - sizeof(struct N##_node*);                          \
                _p_##N##_memswp(((((size_t)(limit - array_)) /                 \
                                  sizeof(struct N##_node*)) /                  \
                                 2) * sizeof(struct N##_node*) +               \
                                    array_,                                    \
                                array_);                                       \
                if (_p_##_p_##N##_node_compare(i, j, comp) > 0) {              \
                    _p_##N##_memswp(i, j);                                     \
                }                                                              \
                if (_p_##_p_##N##_node_compare(array_, j, comp) > 0) {         \
                    _p_##N##_memswp(array_, j);                                \
                }                                                              \
                if (_p_##_p_##N##_node_compare(i, array_, comp) > 0) {         \
                    _p_##N##_memswp(i, array_);                                \
                }                                                              \
                while (1) {                                                    \
                    do {                                                       \
                        i += sizeof(struct N##_node*);                         \
                    } while (_p_##_p_##N##_node_compare(array_, i, comp) > 0); \
                    do {                                                       \
                        j -= sizeof(struct N##_node*);                         \
                    } while (_p_##_p_##N##_node_compare(j, array_, comp) > 0); \
                    if (i > j) {                                               \
                        break;                                                 \
                    }                                                          \
                    _p_##N##_memswp(i, j);                                     \
                }                                                              \
                _p_##N##_memswp(array_, j);                                    \
                if (j - array_ > limit - i) {                                  \
                    SGC_STACK_PUSH(array_, j);                                 \
                    array_ = i;                                                \
                } else {                                                       \
                    SGC_STACK_PUSH(i, limit);                                  \
                    limit = j;                                                 \
                }                                                              \
            } else {                                                           \
                for (j = array_, i = j + sizeof(struct N##_node*); i < limit;  \
                     j = i, i += sizeof(struct N##_node*)) {                   \
                    for (;                                                     \
                         _p_##_p_##N##_node_compare(j,                         \
                                                    j + sizeof(                \
                                                            struct N##_node*), \
                                                    comp) > 0;                 \
                         j -= sizeof(struct N##_node*)) {                      \
                        _p_##N##_memswp(j, j + sizeof(struct N##_node*));      \
                        if (j == array_) {                                     \
                            break;                                             \
                        }                                                      \
                    }                                                          \
                }                                                              \
                if (stackptr != stack) {                                       \
                    SGC_STACK_POP(array_, limit);                              \
                } else {                                                       \
                    break;                                                     \
                }                                                              \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_init(struct N* l) {                                               \
        l->size_ = 0;                                                          \
        l->head_ = l->tail_ = NULL;                                            \
        l->shared_ = 0;                                                        \
    }                                                                          \
                                                                               \
    void N##_free(struct N* l) {                                               \
        struct N##_node* curr = l->head_;                                      \
        struct N##_node* tmp;                                                  \
        for (size_t i = 0; i < l->size_; ++i) {                                \
            tmp = curr;                                                        \
            curr = curr->next_;                                                \
            if (!l->shared_) {                                                 \
                T##_free(&tmp->data_);                                         \
            }                                                                  \
            _p_##N##_node_free(l, tmp);                                        \
        }                                                                      \
        l->head_ = l->tail_ = NULL;                                            \
        l->size_ = 0;                                                          \
    }                                                                          \
                                                                               \
    T* N##_back(struct N* l) {                                                 \
        T* ret = NULL;                                                         \
        if (l->size_) {                                                        \
            ret = &l->tail_->data_;                                            \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_set_back(struct N* l, T new_el) {                                 \
        if (l->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, l->tail_->data_, new_el,           \
                        l->shared_);                                           \
        }                                                                      \
    }                                                                          \
                                                                               \
    T* N##_front(struct N* l) {                                                \
        T* ret = NULL;                                                         \
        if (l->size_) {                                                        \
            ret = &l->head_->data_;                                            \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    T* N##_set_front(struct N* l, T new_el) {                                  \
        T* ret = NULL;                                                         \
        if (l->size_) {                                                        \
            SGC_REPLACE(T##_copy, T##_free, l->head_->data_, new_el,           \
                        l->shared_);                                           \
        }                                                                      \
        return ret;                                                            \
    }                                                                          \
                                                                               \
    void N##_sort(struct N* l, int (*comp)(const void*, const void*)) {        \
        struct N##_node** nodes_ptr = (struct N##_node**)sgc_malloc(           \
            sizeof(struct N##_node*) * l->size_);                              \
        struct N##_node* curr = l->head_;                                      \
                                                                               \
        for (size_t i = 0; i < l->size_; i++) {                                \
            nodes_ptr[i] = curr;                                               \
            curr = curr->next_;                                                \
        }                                                                      \
                                                                               \
        _p_##N##_qsort(nodes_ptr, l->size_, comp);                             \
        _p_##N##_ptr_array_to_list(nodes_ptr, l);                              \
        sgc_free(nodes_ptr);                                                   \
    }                                                                          \
                                                                               \
    T* N##_it_data(struct N##_it i) {                              \
        return &i.curr_->data_;                                                \
    }                                                                          \
                                                                               \
    const T* N##_it_cdata(const struct N##_it i) {                 \
        return &i.curr_->data_;                                                \
    }                                                                          \
                                                                               \
    void N##_it_go_next(struct N##_it* i) {                           \
        i->curr_ = i->curr_->next_;                                            \
    }                                                                          \
                                                                               \
    bool N##_it_equal(const struct N##_it first,                   \
                            const struct N##_it second) {                \
        return first.curr_ == second.curr_;                                    \
    }                                                                          \
                                                                               \
    bool N##_it_valid(const struct N##_it i) {                     \
        return i.curr_ != NULL;                                                \
    }                                                                          \
                                                                               \
    struct N##_it N##_end(struct N* l) {                                 \
        struct N##_it i;                                                 \
        N##_it_end(l, &i);                                               \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cend(const struct N* const l) {                    \
        struct N##_it i;                                                 \
        N##_it_cend(l, &i);                                              \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_begin(struct N* l) {                               \
        struct N##_it i;                                                 \
        N##_it_begin(l, &i);                                             \
        return i;                                                              \
    }                                                                          \
                                                                               \
    struct N##_it N##_cbegin(const struct N* const l) {                  \
        struct N##_it i;                                                 \
        N##_it_cbegin(l, &i);                                            \
        return i;                                                              \
    }
