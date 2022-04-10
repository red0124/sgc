#include "test_common.h"
#include <sgc/fs_queue.h>

#define TEST_ELEMENTS_NUM 50
#define QUEUE_MAX 512

SGC_INIT_FS_QUEUE(int, QUEUE_MAX, queue)

void test_queue_insert_erase_combinations(void) {
    TEST_TQ(queue);
}

void test_queue_copy(void) {
    queue v;
    queue_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        queue_push(&v, i);
    }

    queue v_cp;
    queue_copy(&v_cp, &v);

    TEST_ASSERT_EQUAL_INT(queue_size(&v), queue_size(&v_cp));
    // TODO update TEST_ASSERT_EQUAL_INT(1, queue_equal(&v_cp, &v));

    queue_free(&v);
    queue_free(&v_cp);
}

void test_queue_front_back(void) {
    queue q;
    queue_init(&q);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        queue_push(&q, i);
        TEST_ASSERT_EQUAL_INT(0, *queue_front(&q));
        return;
        TEST_ASSERT_EQUAL_INT(i, *queue_back(&q));
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(i, *queue_front(&q));
        TEST_ASSERT_EQUAL_INT(TEST_ELEMENTS_NUM - 1, *queue_back(&q));
        queue_pop(&q);
    }

    queue_free(&q);
}

SGC_INIT_FS_QUEUE(al, QUEUE_MAX, aqueue)

void test_aqueue(void) {
    aqueue v;
    aqueue_init(&v);

    int x = 0;
    al tmp = {&x};

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        aqueue_push(&v, tmp);
    }

    aqueue_pop(&v);

    aqueue_set_shareing(&v);
    ++allocation_count;
    aqueue_push(&v, (al){(int*)malloc(sizeof(int))});
    aqueue_set_owning(&v);

    aqueue_free(&v);

    TEST_ASSERT_EQUAL_INT(0, allocation_count);
    // no memory should be left dealocated
}

SGC_INIT_FS_QUEUE(queue, QUEUE_MAX, vqueue)

const int* vqueue_front_pair(vqueue* l) {
    return queue_front(vqueue_front(l));
}

const int* vqueue_back_pair(vqueue* l) {
    return queue_back(vqueue_back(l));
}

const int* vqueue_back_front_pair(vqueue* l) {
    return queue_back(vqueue_front(l));
}

const int* vqueue_front_back_pair(vqueue* l) {
    return queue_front(vqueue_back(l));
}

void test_queue_queue(void) {
    vqueue v;
    vqueue_init(&v);

    queue tmp;
    queue_init(&tmp);

    queue_push(&tmp, 0);
    // {0}

    vqueue_push(&v, tmp);
    // pushed queue into vqueue, it will make a copy

    queue_push(&tmp, 1);
    // {0, 1}

    vqueue_push(&v, tmp);

    queue_push(&tmp, 2);
    // {0, 1, 2}

    vqueue_set_shareing(&v);
    vqueue_push(&v, tmp);
    vqueue_set_owning(&v);
    // pushed queue into vqueue, it will use the original

    // {{0}, {0, 1}, {0, 1, 2}}

    TEST_ASSERT_EQUAL_INT(2, *vqueue_back_pair(&v));
    TEST_ASSERT_EQUAL_INT(0, *vqueue_front_pair(&v));
    TEST_ASSERT_EQUAL_INT(0, *vqueue_front_back_pair(&v));
    TEST_ASSERT_EQUAL_INT(0, *vqueue_back_front_pair(&v));

    vqueue_free(&v);
    // no memory should be left dealocated
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_queue_copy);
    RUN_TEST(test_queue_insert_erase_combinations);
    RUN_TEST(test_queue_front_back);
    RUN_TEST(test_aqueue);
    RUN_TEST(test_queue_queue);

    return UNITY_END();
}
