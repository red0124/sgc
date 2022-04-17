#include "test_common.h"
#include <sgc/fs_priority_queue.h>

#define TEST_ELEMENTS_NUM 50
#define PQUEUE_MAX 512

SGC_INIT_FS_PRIORITY_QUEUE(int, PQUEUE_MAX, pqueue)

void test_fs_pqueue_push_pop_combinations(void) {
    TEST_TPQ(pqueue);
}

SGC_INIT_FS_PRIORITY_QUEUE(oint, PQUEUE_MAX, opqueue)

void test_fs_pqueue_push_pop_combinations_observed(void) {
    TEST_TPQ(opqueue);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_pqueue_push_pop_combinations);
    RUN_TEST(test_fs_pqueue_push_pop_combinations_observed);
    return UNITY_END();
}
