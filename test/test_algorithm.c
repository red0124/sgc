#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define SGC_ST
#include "../lib/deque.h"
#include "../lib/list.h"
#include "../lib/map.h"
#include "../lib/set.h"
#include "../lib/static_types.h"
#include "../lib/static_unordered_map.h"
#include "../lib/string.h"
#include "../lib/unordered_map.h"
#include "../lib/unordered_set.h"
#include "../lib/vector.h"

SGC_INIT_UNORDERED_SET(int, __unused_set);
SGC_INIT_UNORDERED_MAP(int, int, __unused_mat);

#include "../lib/algorithm.h"
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

SGC_INIT_VECTOR(int, vector);
SGC_INIT_DEQUE(int, deque);
SGC_INIT_ALGORITHM(vector);
SGC_INIT_FIND_ITERATOR(vector);

void fold_sum(const int *const el, void *acc)
{
        *(int *)acc += *el;
}

#define SUM(n) ((n) * ((n) + 1) / 2)

void test_fold(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i);
        }

        int sum = 0;
        const int m = TEST_ELEMENTS_NUM;
        vector_fold(&v, fold_sum, &sum);
        TEST_ASSERT_EQUAL_INT(SUM(m - 1), sum);

        sum = 0;
        vector_fold_reverse(&v, fold_sum, &sum);
        TEST_ASSERT_EQUAL_INT(SUM(m - 1), sum);

        sum = 0;
        const int n = 10;
        vector_fold_range(vector_begin(&v), vector_from(&v, n), fold_sum, &sum);
        TEST_ASSERT_EQUAL_INT(SUM(n), sum);

        sum = 0;
        vector_fold_range_reverse(vector_begin(&v), vector_from(&v, n),
                                  fold_sum, &sum);
        TEST_ASSERT_EQUAL_INT(SUM(n), sum);

        const int o = 5;
        sum = 0;
        vector_fold_range(vector_from(&v, o), vector_from(&v, n), fold_sum,
                          &sum);
        TEST_ASSERT_EQUAL_INT(SUM(n) - SUM(o - 1), sum);

        sum = 0;
        vector_fold_range_reverse(vector_from(&v, o), vector_from(&v, n),
                                  fold_sum, &sum);
        TEST_ASSERT_EQUAL_INT(SUM(n) - SUM(o - 1), sum);

        vector_free(&v);
}

int call = 0;

void execute(const int *const el)
{
        (void)el;
        ++call;
}

void test_execute(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i);
        }

        call = 0;
        vector_execute(&v, execute);
        TEST_ASSERT_EQUAL_INT(vector_size(&v), call);

        call = 0;
        vector_execute_reverse(&v, execute);
        TEST_ASSERT_EQUAL_INT(vector_size(&v), call);

        call = 0;
        const int n = 10;
        vector_execute_range(vector_begin(&v), vector_from(&v, n), execute);
        TEST_ASSERT_EQUAL_INT(n + 1, call);

        call = 0;
        vector_execute_range_reverse(vector_begin(&v), vector_from(&v, n),
                                     execute);
        TEST_ASSERT_EQUAL_INT(n + 1, call);

        const int o = 5;
        call = 0;
        vector_execute_range(vector_from(&v, o), vector_from(&v, n), execute);
        TEST_ASSERT_EQUAL_INT(n - o + 1, call);

        call = 0;
        vector_execute_range_reverse(vector_from(&v, o), vector_from(&v, n),
                                     execute);
        TEST_ASSERT_EQUAL_INT(n - o + 1, call);

        vector_free(&v);
}

void test_find(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(0, vector_count(&v, i));
                vector_push_back(&v, i);
        }

        struct vector_iterator it = vector_find(&v, -1);
        TEST_ASSERT_EQUAL_INT(1, vector_iterator_equal(it, vector_end(&v)));
        it = vector_find(&v, TEST_ELEMENTS_NUM);
        TEST_ASSERT_EQUAL_INT(1, vector_iterator_equal(it, vector_end(&v)));

        TEST_ASSERT_EQUAL_INT(NULL, vector_find_el(&v, -1));
        TEST_ASSERT_EQUAL_INT(NULL, vector_find_el(&v, TEST_ELEMENTS_NUM));

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(i, *vector_find_el(&v, i));
                if(i != TEST_ELEMENTS_NUM - 1)
                {
                        it = vector_find(&v, i);
                        TEST_ASSERT_EQUAL_INT(
                            0, vector_iterator_equal(it, vector_end(&v)));
                }
                ssize_t index = vector_find_index(&v, i);
                if(index >= 0)
                {
                        TEST_ASSERT_EQUAL_INT(i, *vector_at(&v, index));
                }
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(1, vector_count(&v, i));
                vector_push_back(&v, i);
                TEST_ASSERT_EQUAL_INT(2, vector_count(&v, i));
                vector_push_back(&v, i);
                TEST_ASSERT_EQUAL_INT(3, vector_count(&v, i));
        }

        vector_free(&v);
}

SGC_INIT_BINARY_FIND(int, vector);

void test_binary_find(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i);
        }

        TEST_ASSERT_EQUAL_INT(NULL, vector_binary_find_el(&v, -1));
        TEST_ASSERT_EQUAL_INT(NULL,
                              vector_binary_find_el(&v, TEST_ELEMENTS_NUM));

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(i, *vector_binary_find_el(&v, i));
                TEST_ASSERT_EQUAL_INT(
                    i, *vector_at(&v, vector_binary_find_index(&v, i)));
        }

        vector_free(&v);
}

SGC_INIT_QSORT(int, vector);

int compare_reverse(const void *const first, const void *const second)
{
        return *(int *)second - *(int *)first;
}

void test_sort(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i % TEST_ELEMENTS_NUM / 4);
        }

        vector_sort(&v, NULL);

        for(size_t i = 1; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(1, *vector_at(&v, i - 1) <=
                                             *vector_at(&v, i));
        }

        vector_sort(&v, compare_reverse);

        for(size_t i = 1; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(1, *vector_at(&v, i) <=
                                             *vector_at(&v, i - 1));
        }

        vector_free(&v);
}

SGC_INIT_MAP(int, int, map);
SGC_INIT_ITERATE(map);

void test_fold_map(void)
{
        map m;
        map_init(&m);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                map_set_at(&m, i, i);
        }

        int sum = 0;
        const int q = TEST_ELEMENTS_NUM;
        map_fold(&m, fold_sum, &sum);
        TEST_ASSERT_EQUAL_INT(SUM(q - 1), sum);

        sum = 0;
        map_fold_reverse(&m, fold_sum, &sum);
        TEST_ASSERT_EQUAL_INT(SUM(q - 1), sum);

        sum = 0;
        map_fold_range_reverse(map_begin(&m), map_end(&m), fold_sum, &sum);
        TEST_ASSERT_EQUAL_INT(SUM(q - 1), sum);

        sum = 0;
        map_fold_range(map_begin(&m), map_end(&m), fold_sum, &sum);
        TEST_ASSERT_EQUAL_INT(SUM(q - 1), sum);

        map_free(&m);
}

SGC_INIT_ITERATE_PAIR(map);

void fold_pair(const int *const k, const int *const v, void *arg)
{
        *(int *)arg += *k + *v * 2;
}

void test_fold_map_pair(void)
{
        map m;
        map_init(&m);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                map_set_at(&m, i, i);
        }

        int sum = 0;
        const int q = TEST_ELEMENTS_NUM;
        map_fold_pair(&m, fold_pair, &sum);
        TEST_ASSERT_EQUAL_INT(3 * SUM(q - 1), sum);

        sum = 0;
        map_fold_reverse_pair(&m, fold_pair, &sum);
        TEST_ASSERT_EQUAL_INT(3 * SUM(q - 1), sum);

        sum = 0;
        map_fold_range_reverse_pair(map_begin(&m), map_end(&m), fold_pair,
                                    &sum);
        TEST_ASSERT_EQUAL_INT(3 * SUM(q - 1), sum);

        sum = 0;
        map_fold_range_pair(map_begin(&m), map_end(&m), fold_pair, &sum);
        TEST_ASSERT_EQUAL_INT(3 * SUM(q - 1), sum);

        map_free(&m);
}

void test_execute_map(void)
{
        map m;
        map_init(&m);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                map_set_at(&m, i, i);
        }

        call = 0;
        map_execute(&m, execute);
        TEST_ASSERT_EQUAL_INT(map_size(&m), call);

        call = 0;
        map_execute_reverse(&m, execute);
        TEST_ASSERT_EQUAL_INT(map_size(&m), call);

        call = 0;
        map_execute_range(map_begin(&m), map_end(&m), execute);
        TEST_ASSERT_EQUAL_INT(map_size(&m), call);

        call = 0;
        map_execute_range_reverse(map_begin(&m), map_end(&m), execute);
        TEST_ASSERT_EQUAL_INT(map_size(&m), call);

        map_free(&m);
}

void execute_pair(const int *const k, const int *const v)
{
        call += *v * 3;
        (void)k;
}

void test_execute_map_pair(void)
{
        map m;
        map_init(&m);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                map_set_at(&m, i, 1);
        }

        call = 0;
        map_execute_pair(&m, execute_pair);
        TEST_ASSERT_EQUAL_INT(3 * map_size(&m), call);

        call = 0;
        map_execute_reverse_pair(&m, execute_pair);
        TEST_ASSERT_EQUAL_INT(3 * map_size(&m), call);

        call = 0;
        map_execute_range_pair(map_begin(&m), map_end(&m), execute_pair);
        TEST_ASSERT_EQUAL_INT(3 * map_size(&m), call);

        call = 0;
        map_execute_range_reverse_pair(map_begin(&m), map_end(&m),
                                       execute_pair);
        TEST_ASSERT_EQUAL_INT(3 * map_size(&m), call);

        map_free(&m);
}

void test_for_each(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i);
        }

        SGC_FOR_EACH(vector, v, i, *i += 1);

        size_t j = 1;
        SGC_FOR_EACH(vector, v, i, TEST_ASSERT_EQUAL_INT(*i, j); ++j);

        vector_free(&v);
}

void test_for_each_pair(void)
{
        map m;
        map_init(&m);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                map_set_at(&m, i, i);
        }

        SGC_FOR_EACH_PAIR(map, m, k, v, (void)k; *v += 1);
        SGC_FOR_EACH_PAIR(map, m, k, v, TEST_ASSERT_EQUAL_INT(*v, *k + 1));

        map_free(&m);
}

SGC_INIT_SET(int, set);

void test_lc1(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i);
        }

        SGC_LC(deque, d, vector, v, x, x + 2, 1);
        SGC_LC(vector, v2, deque, d, x, x * 3);
        SGC_LC(set, s, vector, v2);

        for(size_t i = 0; i < deque_size(&d); ++i)
        {
                TEST_ASSERT_EQUAL_INT(*deque_at(&d, i) - 2, *vector_at(&v, i));
        }

        vector_free(&v);
        vector_free(&v2);
        set_free(&s);
        deque_free(&d);
}

void test_lc2(void)
{
        vector v;
        vector_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                vector_push_back(&v, i);
        }

        vector_push_back(&v, 1);
        SGC_LC(set, s, vector, v, i, i, vector_count(&v, i) == 1);

        TEST_ASSERT_EQUAL_INT(set_size(&s), vector_size(&v) - 2);

        vector_free(&v);
        set_free(&s);
}

SGC_INIT_STRING(string);
SGC_INIT_LIST(string, sset);
SGC_INIT_ALGORITHM(sset);

void test_split(void)
{
        string str = string_create("just some random strings :D :D :D");
        SGC_SPLIT(sset, s, string, str, " ");

        TEST_ASSERT_EQUAL_INT(sset_size(&s), 7);
        TEST_ASSERT_EQUAL_INT(sset_count(&s, (string) "just"), 1);
        TEST_ASSERT_EQUAL_INT(sset_count(&s, (string) "some"), 1);
        TEST_ASSERT_EQUAL_INT(sset_count(&s, (string) "random"), 1);
        TEST_ASSERT_EQUAL_INT(sset_count(&s, (string) "strings"), 1);
        TEST_ASSERT_EQUAL_INT(sset_count(&s, (string) ":D"), 3);

        sset_free(&s);
        string_free(&str);
}

int main(void)
{
        UNITY_BEGIN();
        RUN_TEST(test_fold);
        RUN_TEST(test_execute);
        RUN_TEST(test_find);
        RUN_TEST(test_binary_find);
        RUN_TEST(test_sort);
        RUN_TEST(test_fold_map);
        RUN_TEST(test_fold_map_pair);
        RUN_TEST(test_execute_map);
        RUN_TEST(test_execute_map_pair);
        RUN_TEST(test_for_each);
        RUN_TEST(test_for_each_pair);
        RUN_TEST(test_lc1);
        RUN_TEST(test_lc2);
        RUN_TEST(test_split);

        return UNITY_END();
}
