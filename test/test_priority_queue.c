#include "test_common.h"
#include <sgc/priority_queue.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_PRIORITY_QUEUE(int, pqueue)

void test_pqueue_push_pop_combinations(void) {
    TEST_PUSH_POP_COMBINATIONS_PRIORITY_QUEUE(pqueue);
}

SGC_INIT_PRIORITY_QUEUE(oint, opqueue)

void test_pqueue_push_pop_combinations_observed(void) {
    TEST_PUSH_POP_COMBINATIONS_PRIORITY_QUEUE(opqueue);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pqueue_push_pop_combinations);
    RUN_TEST(test_pqueue_push_pop_combinations_observed);
    return UNITY_END();
}
