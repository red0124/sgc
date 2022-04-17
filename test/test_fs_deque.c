#include "test_common.h"
#include <sgc/fs_deque.h>

#define DEQUE_MAX 512

SGC_INIT_FS_DEQUE(int, DEQUE_MAX, deque)

void test_fs_deque_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(deque, TEST_RANDOM_ACCESS_ITERATOR);
}

SGC_INIT_FS_DEQUE(oint, DEQUE_MAX, odeque)

void test_fs_deque_insert_erase_combinations_observed(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(odeque, TEST_RANDOM_ACCESS_ITERATOR);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_deque_insert_erase_combinations);
    RUN_TEST(test_fs_deque_insert_erase_combinations_observed);
    return UNITY_END();
}
