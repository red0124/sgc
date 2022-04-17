#include "test_common.h"
#include <sgc/queue.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_QUEUE(int, queue)

void test_queue_push_pop_combinations(void) {
    TEST_TQ(queue);
}

SGC_INIT_QUEUE(oint, oqueue)

void test_queue_push_pop_combinations_observed(void) {
    TEST_TQ(oqueue);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_queue_push_pop_combinations);
    RUN_TEST(test_queue_push_pop_combinations_observed);
    return UNITY_END();
}
