#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GC_ST
#include "../lib/gc_static_types.h"
#include "../lib/gc_vector.h"

#include "../lib/gc_static_types.h"

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

INIT_VECTOR(int, vector);

void test_vector_push_pop(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                vector_push_back(&v, i);
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                TEST_ASSERT_EQUAL_INT(i, *vector_at(&v, i));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_pop_back(&v);
        }

        TEST_ASSERT_EQUAL_INT(0, vector_size(&v));

        vector_free(&v);
}

void test_vector_copy(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i);
        }

        vector v_cp;
        vector_copy(&v_cp, &v);

        TEST_ASSERT_EQUAL_INT(1, vector_equal(&v_cp, &v));

        vector_free(&v);
        vector_free(&v_cp);
}

void test_vector_front_back(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i);
                TEST_ASSERT_EQUAL_INT(i, *vector_back(&v));
                TEST_ASSERT_EQUAL_INT(0, *vector_front(&v));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(i, *vector_front(&v));
                TEST_ASSERT_EQUAL_INT(TEST_ELEMENTS_NUM - 1, *vector_back(&v));
                vector_erase_at(&v, 0);
        }

        vector_free(&v);
}

void test_vector_insert_set_at(void)
{
        vector v;
        vector_init(&v);

        vector_push_back(&v, 0);
        vector_push_front(&v, 0);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_insert(&v, i, i);
                TEST_ASSERT_EQUAL_INT(i, *vector_at(&v, i));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_set_at(&v, i, i * 2);
                TEST_ASSERT_EQUAL_INT(i * 2, *vector_at(&v, i));
        }

        vector_free(&v);
}

void test_vector_erase_at(void)
{
        vector v;
        vector_init(&v);

        vector_push_back(&v, 0);
        vector_push_back(&v, 1);
        vector_push_back(&v, 2);
        vector_push_back(&v, 3);
        vector_push_back(&v, 4);
        vector_push_back(&v, 5);

        vector_erase_at(&v, 0);
        TEST_ASSERT_EQUAL_INT(1, *vector_at(&v, 0));

        vector_erase_at(&v, 1);
        TEST_ASSERT_EQUAL_INT(3, *vector_at(&v, 1));

        vector_erase_at(&v, 2);
        TEST_ASSERT_EQUAL_INT(5, *vector_at(&v, 2));

        vector_free(&v);
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

INIT_VECTOR(al, avector);

void test_avector(void)
{
        avector v;
        avector_init(&v);

        int x = 0;
        al tmp = {&x};

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                avector_push_back(&v, tmp);
        }

        avector_pop_back(&v);
        avector_erase_at(&v, avector_size(&v) - 1);

        avector_set_share(1);
        ++allocation_count;
        avector_push_back(&v, (al){(int*)malloc(sizeof(int))});
        avector_set_share(0);

        avector_free(&v);

        TEST_ASSERT_EQUAL_INT(0, allocation_count);
        // no memory should be left dealocated
}

INIT_VECTOR(vector, vvector);
int *vvector_at_pair(vvector *l, size_t m, size_t n)
{
        return vector_at(vvector_at(l, m), n);
}

void test_vector_vector(void)
{
        vvector v;
        vvector_init(&v);

        vector tmp;
        vector_init(&tmp);

        vector_push_back(&tmp, 0);
        // {0}

        vvector_push_back(&v, tmp);
        // pushed vector into vvector, it will make a copy

        vector_push_back(&tmp, 1);
        // {0, 1}

        vvector_push_back(&v, tmp);

        vector_push_back(&tmp, 2);
        // {0, 1, 2}

        vvector_set_share(1);
        vvector_push_back(&v, tmp);
        vvector_set_share(0);
        // pushed vector into vvector, it will use the original

        // {{0}, {0, 1}, {0, 1, 2}}

        TEST_ASSERT_EQUAL_INT(0, *vvector_at_pair(&v, 0, 0));

        TEST_ASSERT_EQUAL_INT(0, *vvector_at_pair(&v, 1, 0));
        TEST_ASSERT_EQUAL_INT(1, *vvector_at_pair(&v, 1, 1));

        TEST_ASSERT_EQUAL_INT(0, *vvector_at_pair(&v, 2, 0));
        TEST_ASSERT_EQUAL_INT(1, *vvector_at_pair(&v, 2, 1));
        TEST_ASSERT_EQUAL_INT(2, *vvector_at_pair(&v, 2, 2));

        vvector_free(&v);
        // no memory should be left dealocated
}

void test_vector_iterator(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i);
        }

        size_t i = 0;

        for(struct vector_iterator it = vector_begin(&v);
            !vector_iterator_equal(it, vector_end(&v));
            vector_iterator_next(&it))
        {
                TEST_ASSERT_EQUAL_INT(*vector_iterator_value(it),
                                      *vector_at(&v, i));
                ++i;
        }

        TEST_ASSERT_EQUAL_INT(*vector_iterator_value(vector_end(&v)),
                              *vector_at(&v, i));

        for(struct vector_iterator it = vector_end(&v);
            !vector_iterator_equal(it, vector_begin(&v));
            vector_iterator_prev(&it))
        {
                TEST_ASSERT_EQUAL_INT(*vector_iterator_value(it),
                                      *vector_at(&v, i));
                --i;
        }

        TEST_ASSERT_EQUAL_INT(*vector_iterator_value(vector_begin(&v)),
                              *vector_at(&v, i));

	i = TEST_ELEMENTS_NUM / 2;
	struct vector_iterator it = vector_from(&v, i);

        TEST_ASSERT_EQUAL_INT(*vector_iterator_value(it),
                              *vector_at(&v, i));


        vector_free(&v);
}

int main(void)
{
        UNITY_BEGIN();
        RUN_TEST(test_vector_push_pop);
        RUN_TEST(test_vector_copy);
        RUN_TEST(test_vector_front_back);
        RUN_TEST(test_vector_insert_set_at);
        RUN_TEST(test_vector_erase_at);
        RUN_TEST(test_avector);
        RUN_TEST(test_vector_vector);
        RUN_TEST(test_vector_iterator);

        return UNITY_END();
}
