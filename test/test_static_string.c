#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SGC_ST
#include "../lib/static_types.h"
#include "../lib/static_string.h"
#include "../lib/algorithm.h"

//#define __UNITY
#ifndef __UNITY
#include "./Unity/src/unity.h"
#else
#define TEST_ASSERT_EQUAL_INT(a, b) (printf((a != b) ? "?\n" : ""))
#define RUN_TEST(x) (x())
#define UNITY_BEGIN() (0)
#define UNITY_END() (1)
#endif

#define TEST_ELEMENTS_NUM 20

SGC_INIT_STATIC(STRING, 128, string);

void test_string_push_pop(void)
{
        string v;
        string_init(&v);

        for(size_t i = 'a'; i < TEST_ELEMENTS_NUM + 'a'; ++i)
        {
                string_push_back(&v, i);
        }

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                TEST_ASSERT_EQUAL_INT(i + 'a', v[i]);
        }

        for(size_t i = 'a'; i < TEST_ELEMENTS_NUM + 'a'; ++i)
        {
                string_pop_back(&v);
        }

        TEST_ASSERT_EQUAL_INT(0, strlen(v));

        string_free(&v);
}

void test_string_copy(void)
{
        string v;
        string_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                string_push_back(&v, i);
        }

        string v_cp;
        string_copy(&v_cp, &v);

        TEST_ASSERT_EQUAL_INT(1, string_equal(&v_cp, &v));

        string_free(&v);
        string_free(&v_cp);
}

void test_string_iterator(void)
{
        string v;
        string_init(&v);

        for(size_t i = 0; i < TEST_ELEMENTS_NUM; ++i)
        {
                string_push_back(&v, i);
        }

        size_t i = 0;

        for(struct string_iterator it = string_begin(&v);
            !string_iterator_equal(it, string_end(&v));
            string_iterator_next(&it))
        {
                TEST_ASSERT_EQUAL_INT(*string_iterator_value(it), v[i]);
                ++i;
        }

        TEST_ASSERT_EQUAL_INT(*string_iterator_value(string_end(&v)), v[i]);

        for(struct string_iterator it = string_end(&v);
            !string_iterator_equal(it, string_begin(&v));
            string_iterator_prev(&it))
        {
                TEST_ASSERT_EQUAL_INT(*string_iterator_value(it), v[i]);
                --i;
        }

        TEST_ASSERT_EQUAL_INT(*string_iterator_value(string_begin(&v)), v[i]);

        i = TEST_ELEMENTS_NUM / 2;
        struct string_iterator it = string_from(&v, i);

        TEST_ASSERT_EQUAL_INT(*string_iterator_value(it), v[i]);

        string_free(&v);
}

int main(void)
{
        UNITY_BEGIN();
        RUN_TEST(test_string_push_pop);
        RUN_TEST(test_string_copy);
        RUN_TEST(test_string_iterator);

        return UNITY_END();
}
