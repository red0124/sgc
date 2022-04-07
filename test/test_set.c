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
        TEST_ASSERT_EQUAL_INT(i, *set_it_data(set_find(&v, i)));
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        set_erase(&v, i);
    }

    TEST_ASSERT_EQUAL_INT(0, set_size(&v));

    set_free(&v);
}

SGC_INIT_SET(al, aset)

void test_aset(void) {
    aset s;
    aset_init(&s);

    int x = 0;
    al tmp = {&x};

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        aset_insert(&s, tmp);
    }

    x = TEST_ELEMENTS_NUM / 2;
    aset_erase(&s, tmp);
    aset_insert(&s, tmp);
    aset_insert(&s, tmp);
    aset_insert(&s, tmp);

    aset_set_shareing(&s);
    ++allocation_count;
    int* new_el = (int*)malloc(sizeof(int));
    *new_el = TEST_ELEMENTS_NUM + 2;
    tmp.el = new_el;
    aset_insert(&s, tmp);
    aset_set_owning(&s);

    aset_free(&s);

    TEST_ASSERT_EQUAL_INT(0, allocation_count);
    // no memory should be left dealocated
}

int set_compare(const set* const first, const set* const second) {
    return set_size(first) - set_size(second);
}

void test_set_it(void) {
    set v;
    set_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        set_insert(&v, i);
    }

    size_t i = 0;

    for (struct set_it it = set_begin(&v); !set_it_eq(it, set_end(&v));
         set_it_go_next(&it)) {
        TEST_ASSERT_EQUAL_INT(*set_it_data(it), i);
        ++i;
    }

    TEST_ASSERT_EQUAL_INT(*set_it_data(set_end(&v)), TEST_ELEMENTS_NUM - 1);

    for (struct set_it it = set_end(&v); !set_it_eq(it, set_begin(&v));
         set_it_go_prev(&it)) {
        TEST_ASSERT_EQUAL_INT(*set_it_data(it), i);
        --i;
    }

    TEST_ASSERT_EQUAL_INT(*set_it_data(set_begin(&v)), 0);

    set_free(&v);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_set_xxx);
    RUN_TEST(test_set_insert_erase);
    RUN_TEST(test_aset);
    RUN_TEST(test_set_it);

    return UNITY_END();
}
