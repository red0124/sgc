#include "test_common.h"
#include <sgc/priority_queue.h>

SGC_INIT_PRIORITY_QUEUE(int, pqueue)

void test_pqueue_push_pop_combinations(void) {
    TEST_PUSH_POP_COMBINATIONS_PRIORITY_QUEUE(pqueue);
}

SGC_INIT_PRIORITY_QUEUE(oint, opqueue)

void test_pqueue_push_pop_combinations_observed(void) {
    TEST_PUSH_POP_COMBINATIONS_PRIORITY_QUEUE(opqueue);
    ASSERT_ALLOCATION_COUNT
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pqueue_push_pop_combinations);
    RUN_TEST(test_pqueue_push_pop_combinations_observed);

    disable_allocation();
    RUN_TEST(test_pqueue_push_pop_combinations);
    RUN_TEST(test_pqueue_push_pop_combinations_observed);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_pqueue_push_pop_combinations);
    RUN_TEST(test_pqueue_push_pop_combinations_observed);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_pqueue_push_pop_combinations);
    RUN_TEST(test_pqueue_push_pop_combinations_observed);
    return UNITY_END();
}
