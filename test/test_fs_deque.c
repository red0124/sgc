#include "test_common.h"
#include <sgc/fs_deque.h>

#define DEQUE_MAX 512

SGC_INIT_FS_DEQUE(int, DEQUE_MAX, deque)

void test_deque_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(deque, TEST_RANDOM_ACCESS_ITERATOR);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_deque_insert_erase_combinations);
    return UNITY_END();
}
