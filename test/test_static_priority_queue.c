#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../lib/static_priority_queue.h"
#include "./Unity/src/unity.h"

#define TEST_ELEMENTS_NUM 50
#define PQUEUE_MAX 512

SGC_INIT_STATIC_PRIORITY_QUEUE(int, PQUEUE_MAX, pqueue);

void test_pqueue_push_pop(void)
{
        pqueue v;
        pqueue_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                pqueue_push(&v, i);
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                TEST_ASSERT_EQUAL_INT(TEST_ELEMENTS_NUM - 1 - i,
                                      *pqueue_top(&v));
                pqueue_pop(&v);
        }

        TEST_ASSERT_EQUAL_INT(0, pqueue_size(&v));

        pqueue_free(&v);
}

void test_pqueue_copy(void)
{
        pqueue v;
        pqueue_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                pqueue_push(&v, i);
        }

        pqueue v_cp;
        pqueue_copy(&v_cp, &v);

        TEST_ASSERT_EQUAL_INT(1, pqueue_equal(&v_cp, &v));

        pqueue_free(&v);
        pqueue_free(&v_cp);
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

int al_compare(const al *const first, const al *const second)
{
        return *first->el - *second->el;
}

SGC_INIT_STATIC_PRIORITY_QUEUE(al, PQUEUE_MAX, apqueue);

void test_apqueue(void)
{
        apqueue v;
        apqueue_init(&v);

        int x = 0;
        al tmp = {&x};

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                apqueue_push(&v, tmp);
        }

        apqueue_pop(&v);

        apqueue_set_share(&v, 1);
        ++allocation_count;
        al new_el = (al){(int *)malloc(sizeof(int))};
        *(new_el.el) = 3;
        apqueue_push(&v, new_el);
        apqueue_set_share(&v, 0);

        apqueue_free(&v);

        TEST_ASSERT_EQUAL_INT(0, allocation_count);
        // no memory should be left dealocated
}

int pqueue_compare(const struct pqueue *const first,
                   const struct pqueue *const second)
{
        return pqueue_size(first) - pqueue_size(second);
}

SGC_INIT_STATIC_PRIORITY_QUEUE(pqueue, PQUEUE_MAX, vpqueue);
int *vpqueue_top_pair(struct vpqueue *const v)
{
        return pqueue_top(vpqueue_top(v));
}

void test_pqueue_pqueue(void)
{
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

        vpqueue_set_share(&v, 1);
        vpqueue_push(&v, tmp);
        vpqueue_set_share(&v, 0);
        // pushed pqueue into vpqueue, it will use the original

        // {{0}, {0, 1}, {0, 1, 2}}

        TEST_ASSERT_EQUAL_INT(2, *vpqueue_top_pair(&v));

        vpqueue_free(&v);
        // no memory should be left dealocated
}

int main(void)
{
        UNITY_BEGIN();
        RUN_TEST(test_pqueue_push_pop);
        RUN_TEST(test_pqueue_copy);
        RUN_TEST(test_apqueue);
        RUN_TEST(test_pqueue_pqueue);

        return UNITY_END();
}
