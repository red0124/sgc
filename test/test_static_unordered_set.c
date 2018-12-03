#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GC_ST
#include "../lib/gc_static_unordered_set.h"
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
#define SET_MAX 127

INIT_STATIC_UNORDERED_SET(int, SET_MAX, set);

void test_set_insert_erase(void)
{
        set v;
        set_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                set_insert(&v, i);
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                TEST_ASSERT_EQUAL_INT(i, *set_iterator_value(set_find(&v, i)));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                set_erase(&v, i);
        }

        TEST_ASSERT_EQUAL_INT(0, set_size(&v));

        set_free(&v);
}

void test_set_insert_multiple(void)
{
        set v;
        set_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                set_insert_multiple(&v, 0);
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; i++)
        {
                TEST_ASSERT_EQUAL_INT(0, *set_iterator_value(set_find(&v, 0)));
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                set_erase(&v, 0);
        }

	TEST_ASSERT_EQUAL_INT(0, set_iterator_valid(set_find(&v, 0)));
        TEST_ASSERT_EQUAL_INT(0, set_size(&v));

        set_free(&v);
}

void test_set_copy(void)
{
        set v;
        set_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                set_insert(&v, i);
        }

        set v_cp;
        set_copy(&v_cp, &v);

        TEST_ASSERT_EQUAL_INT(1, set_equal(&v_cp, &v));

        set_free(&v);
        set_free(&v_cp);
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

size_t al_hash(const al* const a)
{
	return *a->el;
}

INIT_STATIC_UNORDERED_SET(al, SET_MAX, aset);

void test_aset(void)
{
        aset v;
        aset_init(&v);

        int x = 0;
        al tmp = {&x};

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
		*tmp.el = i;
                aset_insert(&v, tmp);
        }

        x = TEST_ELEMENTS_NUM / 2;
        aset_erase(&v, tmp);
        aset_insert(&v, tmp);
        aset_insert(&v, tmp);
        aset_insert(&v, tmp);

        aset_set_share(1);
        ++allocation_count;
	int* new_el = (int*)malloc(sizeof(int));
	*new_el = TEST_ELEMENTS_NUM + 2;
	tmp.el = new_el;
        aset_insert(&v, tmp);
        aset_set_share(0);

        aset_free(&v);

        TEST_ASSERT_EQUAL_INT(0, allocation_count);
        // no memory should be left dealocated
}

size_t set_hash(const set* const s)
{
	return set_size(s);
}

INIT_STATIC_UNORDERED_SET(set, SET_MAX, vset);

void test_set_set(void)
{
        vset v;
        vset_init(&v);

        set tmp;
        set_init(&tmp);

        set_insert(&tmp, 0);
        // {0}

        vset_insert(&v, tmp);
        // pushed set into vset, it will make a copy

        set_insert(&tmp, 1);
        // {0, 1}

        vset_insert(&v, tmp);

        set_insert(&tmp, 2);
        // {0, 1, 2}

        vset_set_share(1);
        vset_insert(&v, tmp);
        vset_set_share(0);
        // pushed set into vset, it will use the original

        // {{0}, {0, 1}, {0, 1, 2}}

        TEST_ASSERT_EQUAL_INT(
            0, *set_iterator_value(
                   set_find(vset_iterator_value(vset_find(&v, tmp)), 0)));

        vset_free(&v);
        // no memory should be left dealocated
}

void test_set_iterator(void)
{
        set v;
        set_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                set_insert(&v, i);
        }

        size_t i = 0;

        for(struct set_iterator it = set_begin(&v);
            !set_iterator_equal(it, set_end(&v)); set_iterator_next(&it))
        {
                TEST_ASSERT_EQUAL_INT(*set_iterator_value(it), i);
                ++i;
        }

        TEST_ASSERT_EQUAL_INT(*set_iterator_value(set_end(&v)),
                              TEST_ELEMENTS_NUM - 1);

        for(struct set_iterator it = set_end(&v);
            !set_iterator_equal(it, set_begin(&v)); set_iterator_prev(&it))
        {
                TEST_ASSERT_EQUAL_INT(*set_iterator_value(it), i);
                --i;
        }

        TEST_ASSERT_EQUAL_INT(*set_iterator_value(set_begin(&v)), 0);

        set_free(&v);
}

int main(void)
{
        UNITY_BEGIN();
        RUN_TEST(test_set_insert_erase);
        RUN_TEST(test_set_insert_multiple);
        RUN_TEST(test_set_copy);
        RUN_TEST(test_aset);
        RUN_TEST(test_set_set);
        RUN_TEST(test_set_iterator);

        return UNITY_END();
}
