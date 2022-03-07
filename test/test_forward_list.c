#include "test_common.h"
#include <sgc/forward_list.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_FORWARD_LIST(int, list)

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

    TEST_ASSERT_EQUAL_INT(1, list_insert_sorted(&l, 2, int_compare));
    TEST_ASSERT_EQUAL_INT(1, list_insert_sorted(&l, 4, int_compare));
    TEST_ASSERT_EQUAL_INT(1, list_insert_sorted(&l, 3, int_compare));
    TEST_ASSERT_EQUAL_INT(1, list_insert_sorted(&l, 0, int_compare));
    TEST_ASSERT_EQUAL_INT(1, list_insert_sorted(&l, 1, int_compare));
    TEST_ASSERT_EQUAL_INT(1, list_insert_sorted(&l, 5, int_compare));

    TEST_ASSERT_EQUAL_INT(0, *list_at(&l, 0));
    TEST_ASSERT_EQUAL_INT(1, *list_at(&l, 1));
    TEST_ASSERT_EQUAL_INT(2, *list_at(&l, 2));
    TEST_ASSERT_EQUAL_INT(3, *list_at(&l, 3));
    TEST_ASSERT_EQUAL_INT(4, *list_at(&l, 4));
    TEST_ASSERT_EQUAL_INT(5, *list_at(&l, 5));

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

SGC_INIT_FORWARD_LIST(al, alist)

void test_alist(void) {
    alist l;
    alist_init(&l);

    int x = 0;
    al tmp = {&x};

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        alist_push_back(&l, tmp);
    }

    alist_pop_back(&l);
    alist_pop_front(&l);

    alist_set_share(&l, 1);
    ++allocation_count;
    alist_push_back(&l, (al){(int*)malloc(sizeof(int))});
    alist_set_share(&l, 0);

    alist_free(&l);

    TEST_ASSERT_EQUAL_INT(0, allocation_count);
    // no memory should be left dealocated
}

SGC_INIT_FORWARD_LIST(list, llist)
int* llist_at_pair(llist* l, size_t m, size_t n) {
    return list_at(llist_at(l, m), n);
}

void test_list_list(void) {
    llist l;
    llist_init(&l);

    list tmp;
    list_init(&tmp);

    list_push_back(&tmp, 0);
    // {0}

    llist_push_back(&l, tmp);
    // pushed list into llist, it will make a copy

    list_push_back(&tmp, 1);
    // {0, 1}

    llist_push_back(&l, tmp);

    list_push_back(&tmp, 2);
    // {0, 1, 2}

    llist_set_share(&l, 1);
    llist_push_back(&l, tmp);
    llist_set_share(&l, 0);
    // pushed list into llist, it will use the original

    // {{0}, {0, 1}, {0, 1, 2}}

    TEST_ASSERT_EQUAL_INT(0, *llist_at_pair(&l, 0, 0));

    TEST_ASSERT_EQUAL_INT(0, *llist_at_pair(&l, 1, 0));
    TEST_ASSERT_EQUAL_INT(1, *llist_at_pair(&l, 1, 1));

    TEST_ASSERT_EQUAL_INT(0, *llist_at_pair(&l, 2, 0));
    TEST_ASSERT_EQUAL_INT(1, *llist_at_pair(&l, 2, 1));
    TEST_ASSERT_EQUAL_INT(2, *llist_at_pair(&l, 2, 2));

    llist_free(&l);
    // no memory should be left dealocated
}

void test_list_iterator(void) {
    list l;
    list_init(&l);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        list_push_back(&l, i);
    }

    size_t i = 0;

    for (struct list_iterator it = list_begin(&l);
         !list_iterator_equal(it, list_end(&l)); list_iterator_next(&it)) {
        TEST_ASSERT_EQUAL_INT(*list_iterator_data(it), *list_at(&l, i));
        ++i;
    }

    TEST_ASSERT_EQUAL_INT(*list_iterator_data(list_end(&l)), *list_at(&l, i));

    for (struct list_iterator it = list_end(&l);
         !list_iterator_equal(it, list_begin(&l)); list_iterator_prev(&it)) {
        TEST_ASSERT_EQUAL_INT(*list_iterator_data(it), *list_at(&l, i));
        --i;
    }

    TEST_ASSERT_EQUAL_INT(*list_iterator_data(list_begin(&l)), *list_at(&l, i));

    list_free(&l);
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
