#include "test_common.h"
#include <sgc/deque.h>

SGC_INIT_DEQUE(int, deque)

void test_deque_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(deque, TEST_RANDOM_ACCESS_ITERATOR);
}

SGC_INIT_DEQUE(oint, odeque)

void test_deque_insert_erase_combinations_observed(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(odeque, TEST_RANDOM_ACCESS_ITERATOR);
    ASSERT_ALLOCATION_COUNT
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_deque_insert_erase_combinations);
    RUN_TEST(test_deque_insert_erase_combinations_observed);

    disable_allocation();
    RUN_TEST(test_deque_insert_erase_combinations);
    RUN_TEST(test_deque_insert_erase_combinations_observed);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_deque_insert_erase_combinations);
    RUN_TEST(test_deque_insert_erase_combinations_observed);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_deque_insert_erase_combinations);
    RUN_TEST(test_deque_insert_erase_combinations_observed);
    return UNITY_END();
}
