#include "test_common.h"
#include <sgc/fs_queue.h>

#define QUEUE_MAX 512

SGC_INIT_FS_QUEUE(int, QUEUE_MAX, queue)

void test_fs_queue_push_pop_combinations(void) {
    TEST_INSERT_PUSH_POP_COMBINATIONS_QUEUE(queue);
}

SGC_INIT_FS_QUEUE(oint, QUEUE_MAX, oqueue)

void test_fs_queue_push_pop_combinations_observed(void) {
    TEST_INSERT_PUSH_POP_COMBINATIONS_QUEUE(oqueue);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_queue_push_pop_combinations);
    RUN_TEST(test_fs_queue_push_pop_combinations_observed);
    return UNITY_END();
}
