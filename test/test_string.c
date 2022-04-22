#include "test_common.h"
#include <sgc/algorithm.h>
#include <sgc/string.h>
#include <sgc/vector.h>

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

    string_qsort_default(&s);
    ASSERT_EQUAL(false, string_eq(&msg, &s));
    TEST_ASSERT_GREATER_THAN(0, string_compare(&msg, &s));
    TEST_ASSERT_LESS_THAN(0, string_compare(&s, &msg));

    string sorted_msg = "ehllo";
    ASSERT_EQUAL(true, string_eq(&sorted_msg, &s));
    ASSERT_EQUAL(0, string_compare(&sorted_msg, &s));
    ASSERT_EQUAL(0, string_compare(&s, &sorted_msg));

    string_free(&s);
}

SGC_INIT(VECTOR, string, vec)

void test_vector_of_strings(void) {
    vec v;
    vec_init(&v);

    vec_push_back(&v, "hello");
    vec_push_back(&v, "just");
    vec_push_back(&v, "some");
    vec_push_back(&v, "random");
    vec_push_back(&v, "strings");

    ASSERT_EQUAL(vec_size(&v), 5);
    TEST_ASSERT_EQUAL_STRING(*vec_at(&v, 0), "hello");
    TEST_ASSERT_EQUAL_STRING(*vec_at(&v, 1), "just");
    TEST_ASSERT_EQUAL_STRING(*vec_at(&v, 2), "some");
    TEST_ASSERT_EQUAL_STRING(*vec_at(&v, 3), "random");
    TEST_ASSERT_EQUAL_STRING(*vec_at(&v, 4), "strings");

    vec_free(&v);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_empty_string);
    RUN_TEST(test_string_copy_eq_compare);
    RUN_TEST(test_vector_of_strings);
    return UNITY_END();
}
