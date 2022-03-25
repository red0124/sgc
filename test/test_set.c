#include "test_common.h"
#include <sgc/set.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_SET(int, set)

void test_set_xxx(void) {
    TEST_TS(set);
}

void test_set_insert_erase(void) {
    set v;
    set_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; i++) {
        set_insert(&v, i);
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; i++) {
        TEST_ASSERT_EQUAL_INT(i, *set_iterator_data(set_find(&v, i)));
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        set_erase(&v, i);
    }

    TEST_ASSERT_EQUAL_INT(0, set_size(&v));

    set_free(&v);
}

void test_set_insert_multiple(void) {
    set v;
    set_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; i++) {
        set_insert_multiple(&v, 0);
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; i++) {
        TEST_ASSERT_EQUAL_INT(0, *set_iterator_data(set_find(&v, 0)));
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        set_erase(&v, 0);
    }

    TEST_ASSERT_EQUAL_INT(0, set_iterator_valid(set_find(&v, 0)));
    TEST_ASSERT_EQUAL_INT(0, set_size(&v));

    set_free(&v);
}

/* TODO update
void test_set_copy(void) {
    set v;
    set_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        set_insert(&v, i);
    }

    set v_cp;
    set_copy(&v_cp, &v);

    TEST_ASSERT_EQUAL_INT(1, set_equal(&v_cp, &v));

    set_free(&v);
    set_free(&v_cp);
} */

SGC_INIT_SET(al, aset)

void test_aset(void) {
    aset v;
    aset_init(&v);

    int x = 0;
    al tmp = {&x};

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        aset_insert(&v, tmp);
    }

    x = TEST_ELEMENTS_NUM / 2;
    aset_erase(&v, tmp);
    aset_insert(&v, tmp);
    aset_insert(&v, tmp);
    aset_insert(&v, tmp);

    aset_set_share(&v, 1);
    ++allocation_count;
    int* new_el = (int*)malloc(sizeof(int));
    *new_el = TEST_ELEMENTS_NUM + 2;
    tmp.el = new_el;
    aset_insert(&v, tmp);
    aset_set_share(&v, 0);

    aset_free(&v);

    TEST_ASSERT_EQUAL_INT(0, allocation_count);
    // no memory should be left dealocated
}

int set_compare(const set* const first, const set* const second) {
    return set_size(first) - set_size(second);
}

/* TODO update
SGC_INIT_SET(set, vset)

void test_set_set(void) {
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

    vset_set_share(&v, 1);
    vset_insert(&v, tmp);
    vset_set_share(&v, 0);
    // pushed set into vset, it will use the original

    // {{0}, {0, 1}, {0, 1, 2}}

    TEST_ASSERT_EQUAL_INT(0,
                          *set_iterator_data(
                              set_find(vset_iterator_data(vset_find(&v, tmp)),
                                       0)));

    vset_free(&v);
    // no memory should be left dealocated
} */

void test_set_iterator(void) {
    set v;
    set_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        set_insert(&v, i);
    }

    size_t i = 0;

    for (struct set_iterator it = set_begin(&v);
         !set_iterator_equal(it, set_end(&v)); set_iterator_next(&it)) {
        TEST_ASSERT_EQUAL_INT(*set_iterator_data(it), i);
        ++i;
    }

    TEST_ASSERT_EQUAL_INT(*set_iterator_data(set_end(&v)),
                          TEST_ELEMENTS_NUM - 1);

    for (struct set_iterator it = set_end(&v);
         !set_iterator_equal(it, set_begin(&v)); set_iterator_prev(&it)) {
        TEST_ASSERT_EQUAL_INT(*set_iterator_data(it), i);
        --i;
    }

    TEST_ASSERT_EQUAL_INT(*set_iterator_data(set_begin(&v)), 0);

    set_free(&v);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_set_xxx);
    RUN_TEST(test_set_insert_erase);
    RUN_TEST(test_set_insert_multiple);
    // TODO update RUN_TEST(test_set_copy);
    RUN_TEST(test_aset);
    // TODO update RUN_TEST(test_set_set);
    RUN_TEST(test_set_iterator);

    return UNITY_END();
}
