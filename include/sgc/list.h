#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_dll_type.h"
#include "detail/sgc_list_type.h"
#include "detail/sgc_sort_stack.h"
#include "detail/sgc_utils.h"
#include <stdbool.h>

#define _SGC_INIT_PRIVATE_LIST_FUNCTION_DECLARATIONS(T, N)                     \
    static void _m_##N##_memswp(char* i, char* j);                             \
    static bool _m_##N##_compare_node(const void* const first,                 \
                                      const void* const second,                \
                                      int comp(const void*, const void*));     \
    static void _m_##N##_qsort(void* array, size_t array_size,                 \
                               int (*comp)(const void*, const void*));         \
    static void _m_##N##_ptr_array_to_list(struct _m_##N##_node** nodes_ptr,   \
                                           struct N* l);                       \
    static struct _m_##N##_node* _m_##N##_node_alloc(struct N* l);             \
    static void _m_##N##_node_free(struct N* l, struct _m_##N##_node* n);

#define SGC_INIT_HEADERS_LIST(T, N)                                            \
                                                                               \
    struct _m_##N##_node {                                                     \
        T data_;                                                               \
        struct _m_##N##_node* next_;                                           \
        struct _m_##N##_node* prev_;                                           \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t size_;                                                          \
        size_t shared_;                                                        \
        struct _m_##N##_node* head_;                                           \
        struct _m_##N##_node* tail_;                                           \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    void N##_set_share(N* l, int is_shared);                                   \
    size_t N##_size(const struct N* const l);                                  \
    void N##_init(struct N* l);                                                \
    void N##_free(struct N* l);                                                \
    bool N##_equal(const struct N* const first, const struct N* const second); \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src);                     \
    void N##_push_back(struct N* l, T el);                                     \
    T* N##_back(struct N* l);                                                  \
    void N##_set_back(struct N* l, T new_el);                                  \
    void N##_pop_back(struct N* l);                                            \
    void N##_push_front(struct N* l, const T el);                              \
    T* N##_front(struct N* l);                                                 \
    T* N##_set_front(struct N* l, T new_el);                                   \
    void N##_pop_front(struct N* l);                                           \
    bool N##_empty(const struct N* l);                                         \
    void N##_sort(struct N* l, int (*comp)(const void*, const void*));         \
                                                                               \
    struct N##_iterator {                                                      \
        struct _m_##N##_node* curr_;                                           \
    };                                                                         \
                                                                               \
    typedef struct N##_iterator N##_iterator;                                  \
                                                                               \
    T* N##_iterator_data(struct N##_iterator i);                               \
    const T* N##_iterator_cdata(const struct N##_iterator i);                  \
    void N##_iterator_next(struct N##_iterator* i);                            \
    void N##_iterator_prev(struct N##_iterator* i);                            \
    void N##_iterator_begin(struct N* l, struct N##_iterator* i);              \
    void N##_iterator_cbegin(const struct N* const l, struct N##_iterator* i); \
    struct N##_iterator N##_begin(struct N* l);                                \
    struct N##_iterator N##_cbegin(const struct N* const l);                   \
    void N##_iterator_end(struct N* l, struct N##_iterator* i);                \
    void N##_iterator_cend(const struct N* const l, struct N##_iterator* i);   \
    struct N##_iterator N##_end(struct N* l);                                  \
    struct N##_iterator N##_cend(const struct N* const l);                     \
    bool N##_iterator_equal(const struct N##_iterator first,                   \
                            const struct N##_iterator second);                 \
    bool N##_iterator_valid(const struct N##_iterator i);

#define _SGC_INIT_UNIQUE_LIST_FUNCTIONS(T, N)                                  \
    static void _m_##N##_ptr_array_to_list(struct _m_##N##_node** nodes_ptr,   \
                                           struct N* l) {                      \
        if (!l->size_) {                                                       \
            return;                                                            \
        }                                                                      \
                                                                               \
        l->head_ = nodes_ptr[0];                                               \
        l->head_->prev_ = NULL;                                                \
                                                                               \
        l->tail_ = nodes_ptr[l->size_ - 1];                                    \
        l->tail_->next_ = NULL;                                                \
                                                                               \
        if (l->size_ > 1) {                                                    \
            l->head_->next_ = nodes_ptr[1];                                    \
            l->tail_->prev_ = nodes_ptr[l->size_ - 2];                         \
        }                                                                      \
                                                                               \
        for (size_t i = 1; i < l->size_ - 1; i++) {                            \
            nodes_ptr[i]->prev_ = nodes_ptr[i - 1];                            \
            nodes_ptr[i]->next_ = nodes_ptr[i + 1];                            \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_copy(struct N* __restrict__ dst,                                  \
                  const struct N* __restrict__ const src) {                    \
        dst->shared_ = src->shared_;                                           \
        N##_init(dst);                                                         \
        if (src->size_ != 0) {                                                 \
            dst->head_ = _m_##N##_node_alloc(dst);                             \
            SGC_COPY(T##_copy, dst->head_->data_, src->head_->data_,           \
                     src->shared_);                                            \
            struct _m_##N##_node* curr_src = src->head_;                       \
            struct _m_##N##_node* curr_dst = dst->head_;                       \
            struct _m_##N##_node* tmp_src = NULL;                              \
            struct _m_##N##_node* tmp_dst = NULL;                              \
            while (curr_src) {                                                 \
                tmp_src = curr_src->next_;                                     \
                if (!tmp_src) {                                                \
                    break;                                                     \
                }                                                              \
                tmp_dst = _m_##N##_node_alloc(dst);                            \
                SGC_COPY(T##_copy, tmp_dst->data_, tmp_src->data_,             \
                         src->shared_);                                        \
                tmp_dst->prev_ = curr_dst;                                     \
                curr_dst->next_ = tmp_dst;                                     \
                curr_dst = tmp_dst;                                            \
                curr_src = tmp_src;                                            \
            }                                                                  \
            dst->tail_ = curr_dst;                                             \
            dst->tail_->next_ = dst->head_->prev_ = NULL;                      \
        } else {                                                               \
            dst->head_ = dst->tail_ = NULL;                                    \
        }                                                                      \
        dst->size_ = src->size_;                                               \
    }                                                                          \
                                                                               \
    void N##_push_back(struct N* l, T el) {                                    \
        struct _m_##N##_node* new_el = _m_##N##_node_alloc(l);                 \
        if (!l->shared_) {                                                     \
            T##_copy(&new_el->data_, &el);                                     \
        } else {                                                               \
            new_el->data_ = el;                                                \
        }                                                                      \
        new_el->next_ = NULL;                                                  \
        switch (l->size_) {                                                    \
        case 0:                                                                \
            new_el->prev_ = NULL;                                              \
            l->head_ = l->tail_ = new_el;                                      \
            break;                                                             \
        case 1:                                                                \
            l->tail_ = new_el;                                                 \
            l->head_->next_ = l->tail_;                                        \
            l->tail_->prev_ = l->head_;                                        \
            break;                                                             \
        default:                                                               \
            new_el->prev_ = l->tail_;                                          \
            l->tail_->next_ = new_el;                                          \
            l->tail_ = l->tail_->next_;                                        \
            break;                                                             \
        }                                                                      \
        l->size_++;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_back(struct N* l) {                                           \
        if (l->size_) {                                                        \
            struct _m_##N##_node* tmp = l->tail_;                              \
            l->tail_ = l->tail_->prev_;                                        \
            if (!l->shared_) {                                                 \
                T##_free(&tmp->data_);                                         \
            }                                                                  \
            _m_##N##_node_free(l, tmp);                                        \
            if (l->tail_) {                                                    \
                l->tail_->next_ = NULL;                                        \
            }                                                                  \
            --l->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_push_front(struct N* l, const T el) {                             \
        struct _m_##N##_node* new_el = _m_##N##_node_alloc(l);                 \
        SGC_COPY(T##_copy, new_el->data_, el, l->shared_);                     \
        new_el->prev_ = NULL;                                                  \
        switch (l->size_) {                                                    \
        case 0:                                                                \
            new_el->next_ = NULL;                                              \
            l->head_ = l->tail_ = new_el;                                      \
            break;                                                             \
        case 1:                                                                \
            l->head_ = new_el;                                                 \
            l->head_->next_ = l->tail_;                                        \
            l->tail_->prev_ = l->head_;                                        \
            break;                                                             \
        default:                                                               \
            l->head_->prev_ = new_el;                                          \
            new_el->next_ = l->head_;                                          \
            l->head_ = l->head_->prev_;                                        \
            break;                                                             \
        }                                                                      \
        l->size_++;                                                            \
    }                                                                          \
                                                                               \
    void N##_pop_front(struct N* l) {                                          \
        if (l->size_) {                                                        \
            struct _m_##N##_node* tmp = l->head_;                              \
            l->head_ = l->head_->next_;                                        \
            if (!l->shared_) {                                                 \
                T##_free(&tmp->data_);                                         \
            }                                                                  \
            _m_##N##_node_free(l, tmp);                                        \
            if (l->head_) {                                                    \
                l->head_->prev_ = NULL;                                        \
            }                                                                  \
            --l->size_;                                                        \
        }                                                                      \
    }                                                                          \
                                                                               \
    /* TODO create erase by iterator */                                        \
    __attribute__((                                                            \
        unused)) static void _m_##N##_node_erase(struct N* l,                  \
                                                 struct _m_##N##_node* n) {    \
        if (n->next_) {                                                        \
            n->next_->prev_ = n->prev_;                                        \
        }                                                                      \
        if (n->prev_) {                                                        \
            n->prev_->next_ = n->next_;                                        \
        }                                                                      \
        if (l->shared_) {                                                      \
            T##_free(&n->data_);                                               \
        }                                                                      \
        _m_##N##_node_free(l, n);                                              \
        n = NULL;                                                              \
    }                                                                          \
                                                                               \
    /* TODO create insert by iterator */                                       \
    __attribute__((unused)) static void                                        \
        N##_insert_node(struct _m_##N##_node* __restrict__ curr,               \
                        struct _m_##N##_node* __restrict__ const node_new) {   \
        struct _m_##N##_node* tmp = curr->next_;                               \
        node_new->prev_ = curr;                                                \
        node_new->next_ = tmp;                                                 \
        tmp->prev_ = node_new;                                                 \
        curr->next_ = node_new;                                                \
    }                                                                          \
                                                                               \
    void N##_iterator_prev(struct N##_iterator* i) {                           \
        i->curr_ = i->curr_->prev_;                                            \
    }                                                                          \
                                                                               \
    void N##_iterator_begin(struct N* l, struct N##_iterator* i) {             \
        i->curr_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_cbegin(const struct N* const l,                          \
                             struct N##_iterator* i) {                         \
        i->curr_ = l->head_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_end(struct N* l, struct N##_iterator* i) {               \
        i->curr_ = l->tail_;                                                   \
    }                                                                          \
                                                                               \
    void N##_iterator_cend(const struct N* const l, struct N##_iterator* i) {  \
        i->curr_ = l->tail_;                                                   \
    }

#define SGC_INIT_LIST(T, N)                                                    \
    SGC_INIT_HEADERS_LIST(T, N)                                                \
    _SGC_INIT_PRIVATE_LIST_FUNCTION_DECLARATIONS(T, N)                         \
    _SGC_INIT_COMMON_LIST_TYPE_FUNCTIONS(T, N)                                 \
    _SGC_INIT_UNIQUE_LIST_FUNCTIONS(T, N)                                      \
    _SGC_INIT_COMMON_FUNCTIONS(T, N)
