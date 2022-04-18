#include "test_common.h"
#include <sgc/algorithm.h>
#include <sgc/string.h>

#define TEST_ELEMENTS_NUM 20

SGC_INIT_STRING(string)
SGC_INIT_QSORT(char, string)

void test_empty_string(void) {
    string s;
    string_init(&s);

    string_free(&s);
}

void test_string_copy_eq_compare(void) {
    string s;

    string msg = "hello";
    string_copy(&s, &msg);

    ASSERT_EQUAL(true, string_eq(&msg, &s));
    ASSERT_EQUAL(0, string_compare(&msg, &s));
    ASSERT_EQUAL(0, string_compare(&s, &msg));

    string_sort_default(&s);
    ASSERT_EQUAL(false, string_eq(&msg, &s));
    TEST_ASSERT_GREATER_THAN(0, string_compare(&msg, &s));
    TEST_ASSERT_LESS_THAN(0, string_compare(&s, &msg));

    string sorted_msg = "ehllo";
    ASSERT_EQUAL(true, string_eq(&sorted_msg, &s));
    ASSERT_EQUAL(0, string_compare(&sorted_msg, &s));
    ASSERT_EQUAL(0, string_compare(&s, &sorted_msg));

    string_free(&s);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_string);
    RUN_TEST(test_string_copy_eq_compare);
    return UNITY_END();
}
