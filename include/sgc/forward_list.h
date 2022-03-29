#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_list_common.h"
#include "detail/sgc_sort_stack.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PRIVATE_FORWARD_LIST_FUNCTION_DECLARATIONS(T, N)             \
    static void _p_##N##_memswp(char* i, char* j);                             \
    static inline bool _p_##_p_##N##_node_compare(const void* first,           \
                                                  const void* second,          \
                                                  int comp(const void*,        \
                                                           const void*));      \
    static void _p_##N##_qsort(void* array, size_t array_size,                 \
                               int (*comp)(const void*, const void*));         \
    static void _p_##N##_ptr_array_to_list(struct N##_node** nodes_ptr,        \
                                           struct N* l);                       \
    static struct N##_node* _p_##N##_node_alloc(struct N* l);                  \
    static void _p_##N##_node_free(struct N* l, struct N##_node* n);

#define SGC_INIT_HEADERS_FORWARD_LIST(T, N)                                    \
    struct N##_node {                                                          \
        T data_;                                                               \
        struct N##_node* next_;                                                \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        struct N##_node* head_;                                                \
        struct N##_node* tail_;                                                \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* l, int shared);                                   \
    size_t N##_size(const struct N* const l);                                  \
    void N##_init(struct N* l);                                                \
    void N##_free(struct N* l);                                                \
    bool N##_equal(const struct N* const first, const struct N* const second); \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push_back(struct N* l, T el);                                     \
    T* N##_back(struct N* l);                                                  \
    void N##_set_back(struct N* l, T new_el);                                  \
    void N##_push_front(struct N* l, const T el);                              \
    T* N##_front(struct N* l);                                                 \
    T* N##_set_front(struct N* l, T new_el);                                   \
    void N##_pop_front(struct N* l);                                           \
    bool N##_empty(const struct N* l);                                         \
    void N##_sort(struct N* l, int (*comp)(const void*, const void*));         \
                                                                               \
    struct N##_it {                                                      \
        struct N##_node* curr_;                                                \
        struct N##_node* head_;                                                \
    };                                                                         \
                                                                               \
    typedef struct N##_it N##_it;                                  \
                                                                               \
    T* N##_it_data(struct N##_it i);                               \
    const T* N##_it_cdata(const struct N##_it i);                  \
    void N##_it_go_next(struct N##_it* i);                            \
    void N##_it_begin(struct N* l, struct N##_it* i);              \
    void N##_it_cbegin(const struct N* const l, struct N##_it* i); \
    struct N##_it N##_begin(struct N* l);                                \
    struct N##_it N##_cbegin(const struct N* const l);                   \
    void N##_it_end(struct N* l, struct N##_it* i);                \
    void N##_it_cend(const struct N* const l, struct N##_it* i);   \
    struct N##_it N##_end(struct N* l);                                  \
    struct N##_it N##_cend(const struct N* const l);                     \
    bool N##_it_equal(const struct N##_it first,                   \
                            const struct N##_it second);                 \
    bool N##_it_valid(const struct N##_it i);

#define _SGC_INIT_UNIQUE_FORWARD_LIST_FUNCTIONS(T, N)                          \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        dst->shared_ = src->shared_;                                           \
        N##_init(dst);                                                         \
        if (src->size_ != 0) {                                                 \
            dst->head_ = _p_##N##_node_alloc(dst);                             \
            SGC_COPY(T##_copy, dst->head_->data_, src->head_->data_,           \
                     src->shared_);                                            \
            struct N##_node* curr_src = src->head_;                            \
            struct N##_node* curr_dst = dst->head_;                            \
            struct N##_node* tmp_src = NULL;                                   \
            struct N##_node* tmp_dst = NULL;                                   \
            while (curr_src) {                                                 \
                tmp_src = curr_src->next_;                                     \
                if (!tmp_src) {                                                \
                    break;                                                     \
                }                                                              \
                tmp_dst = _p_##N##_node_alloc(dst);                            \
                SGC_COPY(T##_copy, tmp_dst->data_, tmp_src->data_,             \
                         src->shared_);                                        \
                curr_dst->next_ = tmp_dst;                                     \
                curr_dst = tmp_dst;                                            \
                curr_src = tmp_src;                                            \
            }                                                                  \
            dst->tail_ = curr_dst;                                             \
            dst->tail_->next_ = NULL;                                          \
        } else {                                                               \
            dst->head_ = dst->tail_ = NULL;                                    \
        }                                                                      \
        dst->size_ = src->size_;                                               \
    }                                                                          \
                                                                               \
    void N##_push_back(struct N* l, T el) {                                    \
        struct N##_node* new_el = _p_##N##_node_alloc(l);                      \
        SGC_COPY(T##_copy, new_el->data_, el, l->shared_);                     \
        new_el->next_ = NULL;                                                  \
        switch (l->size_) {                                                    \
        case 0:                                                                \
            l->head_ = l->tail_ = new_el;                                      \
            break;                                                             \
        case 1:                                                                \
            l->tail_ = new_el;                                                 \
            l->head_->next_ = l->tail_;                                        \
            break;                                                             \
        default:                                                               \
            l->tail_->next_ = new_el;                                          \
            l->tail_ = l->tail_->next_;                                        \
            break;                                                             \
        }                                                                      \
        l->size_++;                                                            \
    }                                                                          \
                                                                               \
    void N##_push_front(struct N* l, const T el) {                             \
        struct N##_node* new_el = _p_##N##_node_alloc(l);                      \
        SGC_COPY(T##_copy, new_el->data_, el, l->shared_);                     \
        switch (l->size_) {                                                    \
        case 0:                                                                \
            new_el->next_ = NULL;                                              \
            l->head_ = l->tail_ = new_el;                                      \
            break;                                                             \
        case 1:                                                                \
            l->head_ = new_el;                                                 \
            l->head_->next_ = l->tail_;                                        \
            break;                                                             \
        default:                                                               \
            new_el->next_ = l->head_;                                          \
            l->head_ = new_el;                                                 \
            break;                                                             \
        }                                                                      \
        l->size_++;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_front(struct N* l) {                                          \
        if (l->size_) {                                                        \
            struct N##_node* tmp = l->head_;                                   \
            l->head_ = l->head_->next_;                                        \
            if (!l->shared_) {                                                 \
                T##_free(&tmp->data_);                                         \
            }                                                                  \
            _p_##N##_node_free(l, tmp);                                        \
            --l->size_;                                                        \
            if (l->size_ == 0) {                                               \
                l->tail_ = NULL;                                               \
            }                                                                  \
        }                                                                      \
    }                                                                          \
                                                                               \
    /* TODO use when creating it erase */                                \
    __attribute__(                                                             \
        (unused)) static void _p_##N##_node_erase(struct N* l,                 \
                                                  struct N##_node* n,          \
                                                  struct N##_node* prev) {     \
        if (prev) {                                                            \
            prev->next_ = n->next_;                                            \
        }                                                                      \
        if (!l->shared_) {                                                     \
            T##_free(&n->data_);                                               \
        }                                                                      \
        _p_##N##_node_free(l, n);                                              \
        n = NULL;                                                              \
    }                                                                          \
                                                                               \
    /* TODO use when creating it insert */                               \
    __attribute__((unused)) static void                                        \
        N##_insert_node(struct N##_node* __restrict__ curr,                    \
                        struct N##_node* __restrict__ const node_new) {        \
        struct N##_node* tmp = curr->next_;                                    \
        node_new->next_ = tmp;                                                 \
        curr->next_ = node_new;                                                \
    }                                                                          \
                                                                               \
    static void _p_##N##_ptr_array_to_list(struct N##_node** nodes_ptr,        \
                                           struct N* l) {                      \
        if (!l->size_) {                                                       \
            return;                                                            \
        }                                                                      \
                                                                               \
        l->head_ = nodes_ptr[0];                                               \
                                                                               \
        l->tail_ = nodes_ptr[l->size_ - 1];                                    \
        l->tail_->next_ = NULL;                                                \
                                                                               \
        if (l->size_ > 1) {                                                    \
            l->head_->next_ = nodes_ptr[1];                                    \
        }                                                                      \
                                                                               \
        for (size_t i = 1; i < l->size_ - 1; i++) {                            \
            nodes_ptr[i]->next_ = nodes_ptr[i + 1];                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_it_begin(struct N* l, struct N##_it* i) {             \
        i->curr_ = l->head_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_it_cbegin(const struct N* const l,                          \
                             struct N##_it* i) {                         \
        i->curr_ = l->head_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_it_end(struct N* l, struct N##_it* i) {               \
        i->curr_ = l->tail_;                                                   \
        i->head_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_it_cend(const struct N* const l, struct N##_it* i) {  \
        i->curr_ = l->tail_;                                                   \
        i->head_ = l->head_;                                                   \
    }

#define SGC_INIT_FORWARD_LIST(T, N)                                            \
    SGC_INIT_HEADERS_FORWARD_LIST(T, N)                                        \
    _SGC_INIT_PRIVATE_FORWARD_LIST_FUNCTION_DECLARATIONS(T, N)                 \
    _SGC_INIT_COMMON_LIST_TYPE_FUNCTIONS(T, N)                                 \
    _SGC_INIT_UNIQUE_FORWARD_LIST_FUNCTIONS(T, N)                              \
    _SGC_INIT_COMMON(N)
