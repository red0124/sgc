#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_ST
#include "../lib/static_stack.h"
#include "../lib/static_types.h"

//#define __UNITY
#ifndef __UNITY
#include "./Unity/src/unity.h"
#else
#define TEST_ASSERT_EQUAL_INT(a, b) (printf((a != b) ? "?\n" : ""))
#define RUN_TEST(x) (x())
#define UNITY_BEGIN() (0)
#define UNITY_END() (1)
#endif

#define TEST_ELEMENTS_NUM 50
#define STACK_MAX 512

SGC_INIT_STATIC_STACK(int, STACK_MAX, stack);

void test_stack_copy(void)
{
        stack v;
        stack_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                stack_push(&v, i);
        }

        stack v_cp;
        stack_copy(&v_cp, &v);

        TEST_ASSERT_EQUAL_INT(stack_size(&v), stack_size(&v_cp));
        TEST_ASSERT_EQUAL_INT(1, stack_equal(&v_cp, &v));

        stack_free(&v);
        stack_free(&v_cp);
}

void test_stack_front_back(void)
{
        stack v;
        stack_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                stack_push(&v, i);
                TEST_ASSERT_EQUAL_INT(i, *stack_top(&v));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(TEST_ELEMENTS_NUM - 1 - i,
                                      *stack_top(&v));
                stack_pop(&v);
        }

        stack_free(&v);
}

struct alocated_element
{
        int *el;
};

typedef struct alocated_element al;

size_t allocation_count = 0;

void al_copy(al *dst, const al *const src)
{
        ++allocation_count;
        dst->el = (int *)malloc(sizeof(int));
        *dst->el = *src->el;
}

void al_free(al *a)
{
        --allocation_count;
        free(a->el);
}

int al_equal(const al *const first, const al *const second)
{
        return *first->el == *second->el;
}

SGC_INIT_STATIC_STACK(al, STACK_MAX, astack);

void test_astack(void)
{
        astack v;
        astack_init(&v);

        int x = 0;
        al tmp = {&x};

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                astack_push(&v, tmp);
        }

        astack_pop(&v);

        astack_set_share(1);
        ++allocation_count;
        astack_push(&v, (al){(int *)malloc(sizeof(int))});
        astack_set_share(0);

        astack_free(&v);

        TEST_ASSERT_EQUAL_INT(0, allocation_count);
        // no memory should be left dealocated
}

SGC_INIT_STATIC_STACK(stack, STACK_MAX, vstack);

int *vstack_top_pair(vstack *l)
{
        return stack_top(vstack_top(l));
}

void test_stack_stack(void)
{
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

        vstack_set_share(1);
        vstack_push(&v, tmp);
        vstack_set_share(0);
        // pushed stack into vstack, it will use the original

        // {{0}, {0, 1}, {0, 1, 2}}

        TEST_ASSERT_EQUAL_INT(2, *vstack_top_pair(&v));

        vstack_free(&v);
        // no memory should be left dealocated
}

int main(void)
{
        UNITY_BEGIN();
        RUN_TEST(test_stack_copy);
        RUN_TEST(test_stack_front_back);
        RUN_TEST(test_astack);
        RUN_TEST(test_stack_stack);

        return UNITY_END();
}
