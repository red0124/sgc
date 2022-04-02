#pragma once
#include <stdbool.h>

// FORWARD ITERATOR
#define _SGC_INIT_FWD_IT_PROTOTIPES(N)                                         \
    const N##_type* N##_it_data(const struct N##_it i);                        \
    void N##_it_go_next(struct N##_it* i);                                     \
    void N##_it_begin(struct N* ds, struct N##_it* i);                         \
    void N##_it_cbegin(const struct N* const ds, struct N##_it* i);            \
    struct N##_it N##_begin(struct N* ds);                                     \
    struct N##_it N##_cbegin(const struct N* const ds);                        \
    void N##_it_end(struct N* ds, struct N##_it* i);                           \
    void N##_it_cend(const struct N* const ds, struct N##_it* i);              \
    struct N##_it N##_end(struct N* ds);                                       \
    struct N##_it N##_cend(const struct N* const ds);                          \
    bool N##_it_equal(const struct N##_it first, const struct N##_it second);  \
    bool N##_it_valid(const struct N##_it i);

// BIDIRECTIONAL ITERATOR
#define _SGC_INIT_BD_IT_PROTOTIPES(N)                                          \
    _SGC_INIT_FWD_IT_PROTOTIPES(N)                                             \
    void N##_it_go_prev(struct N##_it* i);

// RANDOM ACCESS ITERATOR
#define _SGC_INIT_RA_IT_PROTOTIPES(N)                                          \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
    void N##_it_from(struct N* ds, struct N##_it* i, size_t at);               \
    void N##_it_cfrom(const struct N* const ds, struct N##_it* i, size_t at);  \
    struct N##_it N##_from(struct N* ds, size_t at);                           \
    struct N##_it N##_cfrom(const struct N* const ds, size_t at);              \
    void N##_it_jump(struct N##_it* i, int range);                             \
    int N##_it_diff(const struct N##_it first, const struct N##_it second);
