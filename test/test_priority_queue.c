#include "test_common.h"
#include <sgc/priority_queue.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_PRIORITY_QUEUE(int, pqueue)

void test_pqueue_xxx(void) {
    TEST_TPQ(pqueue);
}

void test_pqueue_push_pop(void) {
    pqueue v;
    pqueue_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; i++) {
        pqueue_push(&v, i);
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; i++) {
        TEST_ASSERT_EQUAL_INT(TEST_ELEMENTS_NUM - 1 - i, *pqueue_top(&v));
        pqueue_pop(&v);
    }

    TEST_ASSERT_EQUAL_INT(0, pqueue_size(&v));

    pqueue_free(&v);
}

void test_pqueue_copy(void) {
    pqueue v;
    pqueue_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        pqueue_push(&v, i);
    }

    pqueue v_cp;
    pqueue_copy(&v_cp, &v);

    // TODO update this TEST_ASSERT_EQUAL_INT(1, pqueue_equal(&v_cp, &v));

    pqueue_free(&v);
    pqueue_free(&v_cp);
}

SGC_INIT_PRIORITY_QUEUE(al, apqueue)

void test_apqueue(void) {
    apqueue v;
    apqueue_init(&v);

    int x = 0;
    al tmp = {&x};

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        apqueue_push(&v, tmp);
    }

    apqueue_pop(&v);

    apqueue_set_shareing(&v);
    ++allocation_count;
    al new_el = (al){(int*)malloc(sizeof(int))};
    *(new_el.el) = 3;
    apqueue_push(&v, new_el);
    apqueue_set_owning(&v);

    apqueue_free(&v);

    TEST_ASSERT_EQUAL_INT(0, allocation_count);
    // no memory should be left dealocated
}

int pqueue_compare(const struct pqueue* const first,
                   const struct pqueue* const second) {
    return pqueue_size(first) - pqueue_size(second);
}

SGC_INIT_PRIORITY_QUEUE(pqueue, vpqueue)
const int* vpqueue_top_pair(struct vpqueue* const v) {
    return pqueue_top(vpqueue_top(v));
}

void test_pqueue_pqueue(void) {
    vpqueue v;
    vpqueue_init(&v);

    pqueue tmp;
    pqueue_init(&tmp);

    pqueue_push(&tmp, 0);
    // {0}

    vpqueue_push(&v, tmp);
    // pushed pqueue into vpqueue, it will make a copy

    pqueue_push(&tmp, 1);
    // {0, 1}

    vpqueue_push(&v, tmp);

    pqueue_push(&tmp, 2);
    // {0, 1, 2}

    vpqueue_set_shareing(&v);
    vpqueue_push(&v, tmp);
    vpqueue_set_owning(&v);
    // pushed pqueue into vpqueue, it will use the original

    // {{0}, {0, 1}, {0, 1, 2}}

    TEST_ASSERT_EQUAL_INT(2, *vpqueue_top_pair(&v));

    vpqueue_free(&v);
    // no memory should be left dealocated
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_pqueue_xxx);
    RUN_TEST(test_pqueue_push_pop);
    RUN_TEST(test_pqueue_copy);
    RUN_TEST(test_apqueue);
    RUN_TEST(test_pqueue_pqueue);

    return UNITY_END();
}
