#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_ST
#include "../lib/deque.h"
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

SGC_INIT_DEQUE(int, deque);

void test_deque_push_pop(void)
{
        deque v;
        deque_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                deque_push_back(&v, i);
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                TEST_ASSERT_EQUAL_INT(i, *deque_at(&v, i));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                deque_pop_back(&v);
        }

        TEST_ASSERT_EQUAL_INT(0, deque_size(&v));

        deque_free(&v);
}

void test_deque_copy(void)
{
        deque v;
        deque_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                deque_push_back(&v, i);
        }

        deque v_cp;
        deque_copy(&v_cp, &v);

        TEST_ASSERT_EQUAL_INT(1, deque_equal(&v_cp, &v));

        deque_free(&v);
        deque_free(&v_cp);
}

void test_deque_front_back(void)
{
        deque v;
        deque_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                deque_push_back(&v, i);
                TEST_ASSERT_EQUAL_INT(i, *deque_back(&v));
                TEST_ASSERT_EQUAL_INT(0, *deque_front(&v));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(i, *deque_front(&v));
                TEST_ASSERT_EQUAL_INT(TEST_ELEMENTS_NUM - 1, *deque_back(&v));
                deque_erase_at(&v, 0);
        }

        deque_free(&v);
}

void test_deque_insert_set_at(void)
{
        deque v;
        deque_init(&v);

        deque_push_back(&v, 0);
        deque_push_front(&v, 0);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                deque_insert(&v, i, i);
                TEST_ASSERT_EQUAL_INT(i, *deque_at(&v, i));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                deque_set_at(&v, i, i * 2);
                TEST_ASSERT_EQUAL_INT(i * 2, *deque_at(&v, i));
        }

        deque_free(&v);
}

void test_deque_erase_at(void)
{
        deque v;
        deque_init(&v);

        deque_push_back(&v, 0);
        deque_push_back(&v, 1);
        deque_push_back(&v, 2);
        deque_push_back(&v, 3);
        deque_push_back(&v, 4);
        deque_push_back(&v, 5);

        deque_erase_at(&v, 0);
        TEST_ASSERT_EQUAL_INT(1, *deque_at(&v, 0));

        deque_erase_at(&v, 1);
        TEST_ASSERT_EQUAL_INT(3, *deque_at(&v, 1));

        deque_erase_at(&v, 2);
        TEST_ASSERT_EQUAL_INT(5, *deque_at(&v, 2));

        deque_free(&v);
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

SGC_INIT_DEQUE(al, adeque);

void test_adeque(void)
{
        adeque v;
        adeque_init(&v);

        int x = 0;
        al tmp = {&x};

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                adeque_push_back(&v, tmp);
        }

        adeque_pop_back(&v);
        adeque_erase_at(&v, adeque_size(&v) - 1);

        adeque_set_share(1);
        ++allocation_count;
        adeque_push_back(&v, (al){(int *)malloc(sizeof(int))});
        adeque_set_share(0);

        adeque_free(&v);

        TEST_ASSERT_EQUAL_INT(0, allocation_count);
        // no memory should be left dealocated
}

SGC_INIT_DEQUE(deque, vdeque);
int *vdeque_at_pair(vdeque *l, size_t m, size_t n)
{
        return deque_at(vdeque_at(l, m), n);
}

void test_deque_deque(void)
{
        vdeque v;
        vdeque_init(&v);

        deque tmp;
        deque_init(&tmp);

        deque_push_back(&tmp, 0);
        // {0}

        vdeque_push_back(&v, tmp);
        // pushed deque into vdeque, it will make a copy

        deque_push_back(&tmp, 1);
        // {0, 1}

        vdeque_push_back(&v, tmp);

        deque_push_back(&tmp, 2);
        // {0, 1, 2}

        vdeque_set_share(1);
        vdeque_push_back(&v, tmp);
        vdeque_set_share(0);
        // pushed deque into vdeque, it will use the original

        // {{0}, {0, 1}, {0, 1, 2}}

        TEST_ASSERT_EQUAL_INT(0, *vdeque_at_pair(&v, 0, 0));

        TEST_ASSERT_EQUAL_INT(0, *vdeque_at_pair(&v, 1, 0));
        TEST_ASSERT_EQUAL_INT(1, *vdeque_at_pair(&v, 1, 1));

        TEST_ASSERT_EQUAL_INT(0, *vdeque_at_pair(&v, 2, 0));
        TEST_ASSERT_EQUAL_INT(1, *vdeque_at_pair(&v, 2, 1));
        TEST_ASSERT_EQUAL_INT(2, *vdeque_at_pair(&v, 2, 2));

        vdeque_free(&v);
        // no memory should be left dealocated
}

void test_deque_iterator(void)
{
        deque v;
        deque_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                deque_push_back(&v, i);
        }

        size_t i = 0;

        for(struct deque_iterator it = deque_begin(&v);
            !deque_iterator_equal(it, deque_end(&v)); deque_iterator_next(&it))
        {
                TEST_ASSERT_EQUAL_INT(*deque_iterator_value(it),
                                      *deque_at(&v, i));
                ++i;
        }

        TEST_ASSERT_EQUAL_INT(*deque_iterator_value(deque_end(&v)),
                              *deque_at(&v, i));

        for(struct deque_iterator it = deque_end(&v);
            !deque_iterator_equal(it, deque_begin(&v));
            deque_iterator_prev(&it))
        {
                TEST_ASSERT_EQUAL_INT(*deque_iterator_value(it),
                                      *deque_at(&v, i));
                --i;
        }

        TEST_ASSERT_EQUAL_INT(*deque_iterator_value(deque_begin(&v)),
                              *deque_at(&v, i));

        i = TEST_ELEMENTS_NUM / 2;
        struct deque_iterator it = deque_from(&v, i);

        TEST_ASSERT_EQUAL_INT(*deque_iterator_value(it), *deque_at(&v, i));

        deque_free(&v);
}

int main(void)
{
        UNITY_BEGIN();
        RUN_TEST(test_deque_push_pop);
        RUN_TEST(test_deque_copy);
        RUN_TEST(test_deque_front_back);
        RUN_TEST(test_deque_insert_set_at);
        RUN_TEST(test_deque_erase_at);
        RUN_TEST(test_adeque);
        RUN_TEST(test_deque_deque);
        RUN_TEST(test_deque_iterator);

        return UNITY_END();
}
