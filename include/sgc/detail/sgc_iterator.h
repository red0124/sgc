#pragma once
#include <stdbool.h>

// FORWARD ITERATOR
#define _SGC_INIT_FWD_IT_PROTOTIPES(N)                                         \
    N##_type* N##_it_data(N##_it* i);                                          \
    N##_value* N##_it_value(N##_it* i);                                        \
    void N##_it_go_next(N##_it* i);                                            \
    N##_it N##_begin(N* ds);                                                   \
    N##_it N##_cbegin(const N* const ds);                                      \
    void N##_it_end(N* ds, N##_it* i);                                         \
    void N##_it_cend(const N* const ds, N##_it* i);                            \
    N##_it N##_end(N* ds);                                                     \
    N##_it N##_cend(const N* const ds);                                        \
    bool N##_it_eq(const N##_it* const first, const N##_it* const second);     \
    bool N##_it_valid(const N##_it* const i);

// BIDIRECTIONAL ITERATOR
#define _SGC_INIT_BD_IT_PROTOTIPES(N)                                          \
    _SGC_INIT_FWD_IT_PROTOTIPES(N)                                             \
    void N##_it_go_prev(N##_it* i);

// RANDOM ACCESS ITERATOR
#define _SGC_INIT_RA_IT_PROTOTIPES(N)                                          \
    _SGC_INIT_BD_IT_PROTOTIPES(N)                                              \
    void N##_it_from(N* ds, N##_it* i, size_t at);                             \
    void N##_it_cfrom(const N* const ds, N##_it* i, size_t at);                \
    N##_it N##_from(N* ds, size_t at);                                         \
    void N##_it_move(N##_it* i, int range);                                    \
    int N##_it_diff(const N##_it* const first, const N##_it* const second);

#define _SGC_INIT_IT_CBEGIN_CEND(N)                                            \
    N##_it N##_cend(const N* const v) {                                        \
        return N##_end((N*)v);                                                 \
    }                                                                          \
                                                                               \
    N##_it N##_cbegin(const N* const v) {                                      \
        return N##_begin((N*)v);                                               \
    }

#define _SGC_INIT_IT_CBEGIN_CEND_CFROM(N)                                      \
    _SGC_INIT_IT_CBEGIN_CEND(N)                                                \
    N##_it N##_cfrom(const N* const v, size_t at) {                            \
        return N##_from((N*)v, at);                                            \
    }
