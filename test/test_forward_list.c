#include "test_common.h"
#include <sgc/forward_list.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_FORWARD_LIST(int, list)

#define INIT_ADDITIONAL_FORWARD_LIST_FUNCTIONS(T, N)                           \
    const T* N##_at(N* l, size_t at) {                                         \
        N##_it curr = N##_begin(l);                                            \
                                                                               \
        while (N##_it_valid(curr)) {                                           \
            if (at == 0) {                                                     \
                return N##_it_data(curr);                                      \
            }                                                                  \
            N##_it_go_next(&curr);                                             \
            --at;                                                              \
        }                                                                      \
                                                                               \
        if (at == 0) {                                                         \
            return N##_it_data(curr);                                          \
        }                                                                      \
                                                                               \
        return NULL;                                                           \
    }                                                                          \
                                                                               \
    void N##_set(N* l, size_t at, T el) {                                      \
        int* curr_el = (T*)N##_at(l, at);                                      \
        if (curr_el != NULL) {                                                 \
            *curr_el = el;                                                     \
        }                                                                      \
    }                                                                          \
                                                                               \
    void N##_insert(N* l, int at, T el) {                                      \
        if (at > (int)N##_size(l)) {                                           \
            return;                                                            \
        }                                                                      \
                                                                               \
        N new_list;                                                            \
        N##_init(&new_list);                                                   \
                                                                               \
        for (N##_it curr = N##_begin(l); N##_it_valid(curr);                   \
             N##_it_go_next(&curr)) {                                          \
            if (at == 0) {                                                     \
                N##_push_back(&new_list, el);                                  \
            }                                                                  \
            N##_push_back(&new_list, *N##_it_data(curr));                      \
            --at;                                                              \
        }                                                                      \
                                                                               \
        if (at == 0) {                                                         \
            N##_push_back(&new_list, el);                                      \
        }                                                                      \
                                                                               \
        N##_free(l);                                                           \
        *l = new_list;                                                         \
    }                                                                          \
                                                                               \
    void N##_erase(N* l, int at) {                                             \
        if (at >= (int)N##_size(l)) {                                          \
            return;                                                            \
        }                                                                      \
                                                                               \
        N new_list;                                                            \
        N##_init(&new_list);                                                   \
                                                                               \
        for (N##_it curr = N##_begin(l); N##_it_valid(curr);                   \
             N##_it_go_next(&curr)) {                                          \
            if (at != 0) {                                                     \
                N##_push_back(&new_list, *N##_it_data(curr));                  \
            }                                                                  \
            --at;                                                              \
        }                                                                      \
                                                                               \
        N##_free(l);                                                           \
        *l = new_list;                                                         \
    }                                                                          \
    void N##_pop_back(N* l) {                                                  \
        if (!N##_empty(l)) {                                                   \
            N##_erase(l, N##_size(l) - 1);                                     \
        }                                                                      \
    }

INIT_ADDITIONAL_FORWARD_LIST_FUNCTIONS(int, list)

void test_list_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(list, TEST_FORWARD_ITERATOR);
}

SGC_INIT_FORWARD_LIST(oint, olist)
INIT_ADDITIONAL_FORWARD_LIST_FUNCTIONS(oint, olist)

void test_list_insert_erase_combinations_observed(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(olist, TEST_FORWARD_ITERATOR);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_insert_erase_combinations);
    RUN_TEST(test_list_insert_erase_combinations_observed);
    return UNITY_END();
}
