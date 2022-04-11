#include "test_common.h"
#include <sgc/deque.h>

SGC_INIT_DEQUE(int, deque)

void test_deque_insert_erase_combinations(void) {
    TEST_INSERT_ERASE_COMBINATIONS_ARRAY(deque);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_deque_insert_erase_combinations);
    return UNITY_END();
}
