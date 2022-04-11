#include "test_common.h"
#include <sgc/stack.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_STACK(int, stack)

void test_stack_insert_erase_combinations(void) {
    TEST_TSTK(stack);
}

void test_stack_copy(void) {
    stack v;
    stack_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        stack_push(&v, i);
    }

    stack v_cp;
    stack_copy(&v_cp, &v);

    TEST_ASSERT_EQUAL_INT(stack_size(&v), stack_size(&v_cp));
    // TODO UPDATE THIS   TEST_ASSERT_EQUAL(true, stack_equal(&v_cp, &v));

    stack_free(&v);
    stack_free(&v_cp);
}

void test_stack_front_back(void) {
    stack v;
    stack_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        stack_push(&v, i);
        TEST_ASSERT_EQUAL_INT(i, *stack_top(&v));
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(TEST_ELEMENTS_NUM - 1 - i, *stack_top(&v));
        stack_pop(&v);
    }

    stack_free(&v);
}

SGC_INIT_STACK(al, astack)

void test_astack(void) {
    astack v;
    astack_init(&v);

    int x = 0;
    al tmp = {&x};

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        astack_push(&v, tmp);
    }

    astack_pop(&v);

    astack_set_shareing(&v);
    ++allocation_count;
    astack_push(&v, (al){(int*)malloc(sizeof(int))});
    astack_set_owning(&v);

    astack_free(&v);

    TEST_ASSERT_EQUAL_INT(0, allocation_count);
    // no memory should be left dealocated
}

SGC_INIT_STACK(stack, vstack)

int* vstack_top_pair(vstack* l) {
    return stack_top(vstack_top(l));
}

void test_stack_stack(void) {
    vstack v;
    vstack_init(&v);

    stack tmp;
    stack_init(&tmp);

    stack_push(&tmp, 0);
    // {0}

    vstack_push(&v, tmp);
    // pushed stack into vstack, it will make a copy

    stack_push(&tmp, 1);
    // {0, 1}

    vstack_push(&v, tmp);

    stack_push(&tmp, 2);
    // {0, 1, 2}

    vstack_set_shareing(&v);
    vstack_push(&v, tmp);
    vstack_set_owning(&v);
    // pushed stack into vstack, it will use the original

    // {{0}, {0, 1}, {0, 1, 2}}

    TEST_ASSERT_EQUAL_INT(2, *vstack_top_pair(&v));

    vstack_free(&v);
    // no memory should be left dealocated
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stack_insert_erase_combinations);
    RUN_TEST(test_stack_copy);
    RUN_TEST(test_stack_front_back);
    RUN_TEST(test_astack);
    RUN_TEST(test_stack_stack);

    return UNITY_END();
}
