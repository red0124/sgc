#include "test_common.h"
#include <sgc/deque.h>

SGC_INIT_DEQUE(int, deque)

void test_deque_push_pop_front_back(void) {
    TEST_PUSH_BACK_POP_BACK_AT_FRONT_BACK_EMPTY(deque);
}

void test_deque_copy(void) {
    TEST_PUSH_BACK_COPY_EQUAL(deque);
}

void test_deque_insert(void) {
    TEST_AT_INSERT(deque);
}

void test_deque_erase_at(void) {
    TEST_PUSH_BACK_AT_ERASE_AT(deque);
}

void test_deque_insert_set(void) {
    TEST_PUSH_BACK_AT_SET_SET_AT_SET_FRONT_SET_BACK(deque);
}

SGC_INIT_DEQUE(al, adeque)

void test_adeque(void) {
    TEST_PUSH_BACK_ERASE_AT_ALLOCATIONS(adeque);
}

SGC_INIT_DEQUE(deque, ddeque)

void test_deque_deque(void) {
    TEST_ARRAY_OF_ARRAYS_PUSH_BACK_AT_SHARE(ddeque, deque);
}

void test_deque_iterator(void) {
    TEST_PUSH_BACK_ITERATOR(deque);
}

void test_deque_iterator_from(void) {
    TEST_PUSH_BACK_ITERATOR_FROM(deque);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_deque_push_pop_front_back);
    RUN_TEST(test_deque_copy);
    RUN_TEST(test_deque_insert);
    RUN_TEST(test_deque_insert_set);
    RUN_TEST(test_deque_erase_at);
    RUN_TEST(test_adeque);
    RUN_TEST(test_deque_deque);
    RUN_TEST(test_deque_iterator);
    RUN_TEST(test_deque_iterator_from);

    return UNITY_END();
}
