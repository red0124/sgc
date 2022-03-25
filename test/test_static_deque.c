#include "test_common.h"
#include <sgc/static_deque.h>

#define DEQUE_MAX 512

SGC_INIT_STATIC_DEQUE(int, DEQUE_MAX, deque)

void test_static_deque_push_pop_front_back(void) {
    // TEST_PUSH_BACK_POP_BACK_AT_FRONT_BACK_EMPTY(deque);
    TEST_TA(deque);
}

void test_static_deque_copy(void) {
    TEST_PUSH_BACK_COPY_EQUAL(deque);
}

void test_static_deque_insert(void) {
    TEST_AT_INSERT(deque);
}

void test_static_deque_erase_at(void) {
    TEST_PUSH_BACK_AT_ERASE_AT(deque);
}

void test_static_deque_insert_set(void) {
    TEST_PUSH_BACK_AT_SET_SET_AT_SET_FRONT_SET_BACK(deque);
}

SGC_INIT_STATIC_DEQUE(al, DEQUE_MAX, adeque)

void test_astatic_deque(void) {
    TEST_PUSH_BACK_ERASE_AT_ALLOCATIONS(adeque);
}

SGC_INIT_STATIC_DEQUE(deque, DEQUE_MAX, ddeque)

void test_static_deque_static_deque(void) {
    TEST_ARRAY_OF_ARRAYS_PUSH_BACK_AT_SHARE(ddeque, deque);
}

void test_static_deque_iterator(void) {
    TEST_PUSH_BACK_ITERATOR(deque);
}

void test_static_deque_iterator_from(void) {
    TEST_PUSH_BACK_ITERATOR_FROM(deque);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_static_deque_push_pop_front_back);
    RUN_TEST(test_static_deque_copy);
    RUN_TEST(test_static_deque_insert);
    RUN_TEST(test_static_deque_insert_set);
    RUN_TEST(test_static_deque_erase_at);
    RUN_TEST(test_astatic_deque);
    RUN_TEST(test_static_deque_static_deque);
    RUN_TEST(test_static_deque_iterator);
    RUN_TEST(test_static_deque_iterator_from);

    return UNITY_END();
}
