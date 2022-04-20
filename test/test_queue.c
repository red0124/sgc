#define LOG
#include "test_common.h"
#include <sgc/queue.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_QUEUE(int, queue)

void test_queue_push_pop_combinations(void) {
    TEST_PUSH_POP_COMBINATIONS_QUEUE(queue);
}

SGC_INIT_QUEUE(oint, oqueue)

void test_queue_push_pop_combinations_observed(void) {
    TEST_PUSH_POP_COMBINATIONS_QUEUE(oqueue);
    ASSERT_ALLOCATION_COUNT
}

void test(void) {
    oqueue q;
    oqueue_init(&q);
    oqueue_set_shareing(&q);

    oqueue_push(&q, 0);
    oqueue_push(&q, 1);
    oqueue_push(&q, 2);
    oqueue_push(&q, 3);
    oqueue_push(&q, 4);
    oqueue_pop(&q);
    oqueue_pop(&q);
    oqueue_pop(&q);
    oqueue_pop(&q);
    oqueue_push(&q, 9);

    oqueue q_copy;
    oqueue_copy(&q_copy, &q);

    printf("%d\n", *oqueue_back(&q));
    printf("%d\n", *oqueue_front(&q));

    oqueue_free(&q);
}

int main(void) {
    UNITY_BEGIN();
    /*
    RUN_TEST(test_queue_push_pop_combinations);
    RUN_TEST(test_queue_push_pop_combinations_observed);

    disable_allocation();
    RUN_TEST(test_queue_push_pop_combinations);
    RUN_TEST(test_queue_push_pop_combinations_observed);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_queue_push_pop_combinations_observed);
    */

    disable_moveing();
    enable_shareing();
    RUN_TEST(test);
    RUN_TEST(test_queue_push_pop_combinations_observed);
    return UNITY_END();
}
