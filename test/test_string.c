#include "test_common.h"
#include <sgc/sgc_string.h>

#define TEST_ELEMENTS_NUM 20

SGC_INIT(STRING, string)

void test_string_push_pop(void) {
    string v;
    string_init(&v);

    for (size_t i = 'a'; i < TEST_ELEMENTS_NUM + 'a'; ++i) {
        string_push_back(&v, i);
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(i + 'a', v[i]);
    }

    for (size_t i = 'a'; i < TEST_ELEMENTS_NUM + 'a'; ++i) {
        string_pop_back(&v);
    }

    TEST_ASSERT_EQUAL_INT(0, strlen(v));

    string_free(&v);
}

void test_string_copy(void) {
    string v;
    string_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        string_push_back(&v, i);
    }

    string v_cp;
    string_copy(&v_cp, &v);

    TEST_ASSERT_EQUAL_INT(1, string_equal(&v_cp, &v));

    string_free(&v);
    string_free(&v_cp);
}

void test_string_it(void) {
    string v;
    string_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        string_push_back(&v, i);
    }

    size_t i = 0;

    for (string_it it = string_begin(&v); !string_it_equal(it, string_end(&v));
         string_it_go_next(&it)) {
        TEST_ASSERT_EQUAL_INT(*string_it_data(it), v[i]);
        ++i;
    }

    TEST_ASSERT_EQUAL_INT(*string_it_data(string_end(&v)), v[i]);

    for (string_it it = string_end(&v); !string_it_equal(it, string_begin(&v));
         string_it_go_prev(&it)) {
        TEST_ASSERT_EQUAL_INT(*string_it_data(it), v[i]);
        --i;
    }

    TEST_ASSERT_EQUAL_INT(*string_it_data(string_begin(&v)), v[i]);

    i = TEST_ELEMENTS_NUM / 2;
    string_it it = string_from(&v, i);

    TEST_ASSERT_EQUAL_INT(*string_it_data(it), v[i]);

    string_free(&v);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_string_push_pop);
    RUN_TEST(test_string_copy);
    RUN_TEST(test_string_it);

    return UNITY_END();
}
