#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GC_ST
#include "../lib/gc_static_types.h"
#include "../lib/gc_static_queue.h"

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
#define QUEUE_MAX 512

INIT_STATIC_QUEUE(int, QUEUE_MAX, queue);

void test_queue_copy(void)
{
        queue v;
        queue_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                queue_push(&v, i);
        }

        queue v_cp;
        queue_copy(&v_cp, &v);

        TEST_ASSERT_EQUAL_INT(queue_size(&v), queue_size(&v_cp));
        TEST_ASSERT_EQUAL_INT(1, queue_equal(&v_cp, &v));

        queue_free(&v);
        queue_free(&v_cp);
}

void test_queue_front_back(void)
{
        queue v;
        queue_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                queue_push(&v, i);
                TEST_ASSERT_EQUAL_INT(i, *queue_back(&v));
                TEST_ASSERT_EQUAL_INT(0, *queue_front(&v));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(i, *queue_front(&v));
                TEST_ASSERT_EQUAL_INT(TEST_ELEMENTS_NUM - 1, *queue_back(&v));
                queue_pop(&v);
        }

        queue_free(&v);
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

INIT_STATIC_QUEUE(al, 512, aqueue);

void test_aqueue(void)
{
        aqueue v;
        aqueue_init(&v);

        int x = 0;
        al tmp = {&x};

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                aqueue_push(&v, tmp);
        }

        aqueue_pop(&v);

        aqueue_set_share(1);
        ++allocation_count;
        aqueue_push(&v, (al){(int*)malloc(sizeof(int))});
        aqueue_set_share(0);

        aqueue_free(&v);

        TEST_ASSERT_EQUAL_INT(0, allocation_count);
        // no memory should be left dealocated
}

INIT_STATIC_QUEUE(queue, QUEUE_MAX, vqueue);

int *vqueue_front_pair(vqueue *l)
{
        return queue_front(vqueue_front(l));
}

int *vqueue_back_pair(vqueue *l)
{
        return queue_back(vqueue_back(l));
}

int *vqueue_back_front_pair(vqueue *l)
{
        return queue_back(vqueue_front(l));
}

int *vqueue_front_back_pair(vqueue *l)
{
        return queue_front(vqueue_back(l));
}

void test_queue_queue(void)
{
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

        vqueue_set_share(1);
        vqueue_push(&v, tmp);
        vqueue_set_share(0);
        // pushed queue into vqueue, it will use the original

        // {{0}, {0, 1}, {0, 1, 2}}

        TEST_ASSERT_EQUAL_INT(2, *vqueue_back_pair(&v));
        TEST_ASSERT_EQUAL_INT(0, *vqueue_front_pair(&v));
        TEST_ASSERT_EQUAL_INT(0, *vqueue_front_back_pair(&v));
        TEST_ASSERT_EQUAL_INT(0, *vqueue_back_front_pair(&v));

        vqueue_free(&v);
        // no memory should be left dealocated
}

int main(void)
{
        UNITY_BEGIN();
        RUN_TEST(test_queue_copy);
        RUN_TEST(test_queue_front_back);
        RUN_TEST(test_aqueue);
        RUN_TEST(test_queue_queue);

        return UNITY_END();
}