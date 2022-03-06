#pragma once

#include "detail/sgc_allocator.h"
#include "detail/sgc_basic_types.h"
#include "detail/sgc_common.h"
#include "detail/sgc_list_type.h"
#include "detail/sgc_sll_type.h"
#include "detail/sgc_sort_stack.h"
#include "detail/sgc_utils.h"

#define SGC_INIT_STATIC_FUNCTIONS_FORWARD_LIST(T, N)                           \
    static struct N##_node* N##_prev(struct N##_node* head,                    \
                                     struct N##_node* n);                      \
    static void N##_node_erase(struct N* l, struct N##_node* n,                \
                               struct N##_node* p);                            \
    static void N##_insert_node(struct N##_node* __restrict__ curr,            \
                                struct N##_node* __restrict__ const node_new); \
    static void N##_memswp(char* i, char* j);                                  \
    static inline int N##_compare_node(const void* first, const void* second,  \
                                       int comp(const void*, const void*));    \
    static void N##_qsort(void* array, size_t array_size,                      \
                          int (*comp)(const void*, const void*));              \
    static void N##_ptr_array_to_list(struct N##_node** nodes_ptr,             \
                                      struct N* l);                            \
    static struct N##_node* N##_node_alloc(struct N* l);                       \
    static void N##_node_free(struct N* l, struct N##_node* n);

#define SGC_INIT_HEADERS_FORWARD_LIST(T, N)                                    \
    struct N##_node {                                                          \
        T _data;                                                               \
        struct N##_node* _next;                                                \
    };                                                                         \
                                                                               \
    struct N {                                                                 \
        size_t _size;                                                          \
        size_t _shared;                                                        \
        struct N##_node* _head;                                                \
        struct N##_node* _tail;                                                \
    };                                                                         \
                                                                               \
    typedef struct N N;                                                        \
    typedef T N##_type;                                                        \
                                                                               \
    /* ================ */                                                     \
    /*  LIST FUNCTIONS  */                                                     \
    /* ================ */                                                     \
                                                                               \
    void N##_set_share(N* l, int is_shared);                                   \
    size_t N##_size(const struct N* const l);                                  \
    void N##_init(struct N* l);                                                \
    void N##_free(struct N* l);                                                \
    int N##_equal(const struct N* const first, const struct N* const second);  \
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
    T* N##_at(struct N* l, const size_t at);                                   \
    void N##_set_at(struct N* l, const size_t at, T new_el);                   \
    int N##_erase(struct N* l, const T el);                                    \
    int N##_erase_at(struct N* l, size_t at);                                  \
    int N##_empty(const struct N* l);                                          \
    void N##_insert(struct N* l, const size_t at, const T el);                 \
    int N##_insert_sorted(struct N* l, const T el,                             \
                          int (*compare)(const T* const, const T* const));     \
    void N##_sort(struct N* l, int (*comp)(const void*, const void*));         \
                                                                               \
    struct N##_iterator {                                                      \
        struct N##_node* _curr;                                                \
        struct N##_node* _head;                                                \
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
    int N##_iterator_equal(const struct N##_iterator first,                    \
                           const struct N##_iterator second);                  \
    int N##_iterator_valid(const struct N##_iterator i);

#define SGC_INIT_FORWARD_LIST(T, N)                                            \
    SGC_INIT_HEADERS_FORWARD_LIST(T, N)                                        \
    SGC_INIT_STATIC_FUNCTIONS_FORWARD_LIST(T, N)                               \
    SGC_INIT_LIST_TYPE_FUNCTIONS(T, 0, N)                                      \
    SGC_INIT_SLL_TYPE_FUNCTIONS(T, 0, N)                                       \
    SGC_INIT_COMMON_FUNCTIONS(T, N)
