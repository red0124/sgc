#include "test_common.h"
#include <sgc/static_list.h>

#define TEST_ELEMENTS_NUM 50
#define LIST_MAX 512

SGC_INIT_STATIC_LIST(int, LIST_MAX, list)

void test_list_push_pop_front_back(void) {
    TEST_PUSH_BACK_POP_BACK_AT_FRONT_BACK_EMPTY(list);
}

void test_list_copy(void) {
    TEST_PUSH_BACK_COPY_EQUAL(list);
}

void test_list_insert_set_at(void) {
    TEST_AT_INSERT(list);
}

void test_list_set_at(void) {
    TEST_PUSH_BACK_AT_SET_SET_AT_SET_FRONT_SET_BACK(list);
}

void test_list_erase(void) {
    TEST_PUSH_BACK_AT_ERASE_AT(list);
}

void test_list_insert_sorted(void) {
    list l;
    list_init(&l);

    ASSERT_EQUAL(1, list_insert_sorted(&l, 2, int_compare));
    ASSERT_EQUAL(1, list_insert_sorted(&l, 4, int_compare));
    ASSERT_EQUAL(1, list_insert_sorted(&l, 3, int_compare));
    ASSERT_EQUAL(1, list_insert_sorted(&l, 0, int_compare));
    ASSERT_EQUAL(1, list_insert_sorted(&l, 1, int_compare));
    ASSERT_EQUAL(1, list_insert_sorted(&l, 5, int_compare));

    ASSERT_EQUAL(0, *list_at(&l, 0));
    ASSERT_EQUAL(1, *list_at(&l, 1));
    ASSERT_EQUAL(2, *list_at(&l, 2));
    ASSERT_EQUAL(3, *list_at(&l, 3));
    ASSERT_EQUAL(4, *list_at(&l, 4));
    ASSERT_EQUAL(5, *list_at(&l, 5));

    list_free(&l);
}

void test_list_sort(void) {
    list l;
    list_init(&l);

    list l_sorted;
    list_init(&l_sorted);

    srand(time(NULL));

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        int el = rand() % (2 * TEST_ELEMENTS_NUM);
        list_push_back(&l, el);
        list_insert_sorted(&l_sorted, el, int_compare);
    }

    list_push_back(&l, 10);
    list_push_back(&l, 30);
    list_push_back(&l, 20);

    list_insert_sorted(&l_sorted, 10, int_compare);
    list_insert_sorted(&l_sorted, 30, int_compare);
    list_insert_sorted(&l_sorted, 20, int_compare);

    list_sort(&l, int_void_compare);

    for (size_t i = 0; i < list_size(&l) - 1; ++i) {
        TEST_ASSERT_EQUAL_INT(1, *list_at(&l, i) <= *list_at(&l, i + 1));

        TEST_ASSERT_EQUAL_INT(1, *list_at(&l_sorted, i) <=
                                     *list_at(&l_sorted, i + 1));
    }

    TEST_ASSERT_EQUAL_INT(1, list_equal(&l, &l_sorted));

    list_free(&l);
    list_free(&l_sorted);
}

SGC_INIT_STATIC_LIST(al, LIST_MAX, alist)

void test_alist(void) {
    TEST_PUSH_BACK_ERASE_AT_ALLOCATIONS(alist);
}

SGC_INIT_STATIC_LIST(list, LIST_MAX, llist)

void test_list_list(void) {
    TEST_ARRAY_OF_ARRAYS_PUSH_BACK_AT_SHARE(llist, list);
}

void test_list_iterator(void) {
    TEST_PUSH_BACK_ITERATOR(list);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_list_push_pop_front_back);
    RUN_TEST(test_list_copy);
    RUN_TEST(test_list_insert_set_at);
    RUN_TEST(test_list_set_at);
    RUN_TEST(test_list_erase);
    RUN_TEST(test_list_insert_sorted);
    RUN_TEST(test_list_sort);
    RUN_TEST(test_alist);
    RUN_TEST(test_list_list);
    RUN_TEST(test_list_iterator);

    return UNITY_END();
}
