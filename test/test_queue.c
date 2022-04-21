#include "test_common.h"
#include <sgc/queue.h>

SGC_INIT_QUEUE(int, queue)

void test_queue_push_pop_combinations(void) {
    TEST_PUSH_POP_COMBINATIONS_QUEUE(queue);
}

SGC_INIT_QUEUE(oint, oqueue)

void test_queue_push_pop_combinations_observed(void) {
    TEST_PUSH_POP_COMBINATIONS_QUEUE(oqueue);
    ASSERT_ALLOCATION_COUNT
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_queue_push_pop_combinations);
    RUN_TEST(test_queue_push_pop_combinations_observed);

    disable_allocation();
    RUN_TEST(test_queue_push_pop_combinations);
    RUN_TEST(test_queue_push_pop_combinations_observed);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_queue_push_pop_combinations);
    RUN_TEST(test_queue_push_pop_combinations_observed);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_queue_push_pop_combinations);
    RUN_TEST(test_queue_push_pop_combinations_observed);
    return UNITY_END();
}
