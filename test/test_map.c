#include "test_common.h"
#include <sgc/map.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_MAP(int, int, map)

void test_map_insert_erase(void) {
    map v;
    map_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; i++) {
        map_set_at(&v, i, i);
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; i++) {
        TEST_ASSERT_EQUAL_INT(i, *map_at(&v, i));
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        map_erase(&v, i);
    }

    TEST_ASSERT_EQUAL_INT(0, map_size(&v));

    map_free(&v);
}

void test_map_copy(void) {
    map v;
    map_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        map_set_at(&v, 0, i);
    }

    map v_cp;
    map_copy(&v_cp, &v);

    TEST_ASSERT_EQUAL_INT(TEST_ELEMENTS_NUM - 1, *map_at(&v_cp, 0));
    TEST_ASSERT_EQUAL_INT(1, map_equal(&v_cp, &v));

    map_free(&v);
    map_free(&v_cp);
}

SGC_INIT_MAP(al, al, amap)

void test_amap(void) {
    amap v;
    amap_init(&v);

    int x = 0;
    al tmp = {&x};

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        x = i;
        amap_at(&v, tmp);
    }

    x = TEST_ELEMENTS_NUM / 2;
    amap_erase(&v, tmp);

    amap_set_share_key(&v, 1);
    ++allocation_count;
    int* new_el = (int*)malloc(sizeof(int));
    *new_el = TEST_ELEMENTS_NUM + 2;
    tmp.el = new_el;
    amap_at(&v, tmp);
    amap_set_share_key(&v, 0);

    amap_free(&v);

    TEST_ASSERT_EQUAL_INT(0, allocation_count);
    // no memory should be left dealocated
}

int map_compare(const map* const first, const map* const second) {
    return map_size(first) - map_size(second);
}

SGC_INIT_MAP(map, map, vmap)

void test_map_map(void) {
    vmap v;
    vmap_init(&v);

    map tmp;
    map_init(&tmp);

    map_set_at(&tmp, 0, 0);
    // {(0, 0)}

    vmap_set_at(&v, tmp, tmp);
    // pushed map into vmap, it will make a copy

    map_set_at(&tmp, 1, 1);
    // {(0, 0) (1, 1)}

    vmap_set_at(&v, tmp, tmp);

    map_set_at(&tmp, 2, 2);
    // {(0, 0), (1, 1), (2, 2)}

    vmap_set_share(&v, 1);
    vmap_set_at(&v, tmp, tmp);
    vmap_set_share(&v, 0);
    // pushed map into vmap, it will use the original

    // {{(0, 0)}, {(0, 0), (1, 1)}, {(0, 0), (1, 1), (2, 2)}}

    TEST_ASSERT_EQUAL_INT(0, *map_at(vmap_at(&v, tmp), 0));
    TEST_ASSERT_EQUAL_INT(1, *map_at(vmap_at(&v, tmp), 1));
    TEST_ASSERT_EQUAL_INT(2, *map_at(vmap_at(&v, tmp), 2));

    vmap_free(&v);
    // no memory should be left dealocated
}

void test_map_iterator(void) {
    map v;
    map_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        map_set_at(&v, i, i);
    }

    size_t i = 0;

    for (struct map_iterator it = map_begin(&v);
         !map_iterator_equal(it, map_end(&v)); map_iterator_next(&it)) {
        TEST_ASSERT_EQUAL_INT(map_iterator_data(it)->value, i);
        ++i;
    }

    TEST_ASSERT_EQUAL_INT(map_iterator_data(map_end(&v))->value,
                          TEST_ELEMENTS_NUM - 1);

    for (struct map_iterator it = map_end(&v);
         !map_iterator_equal(it, map_begin(&v)); map_iterator_prev(&it)) {
        TEST_ASSERT_EQUAL_INT(map_iterator_data(it)->value, i);
        --i;
    }

    TEST_ASSERT_EQUAL_INT(map_iterator_data(map_begin(&v))->value, 0);

    map_free(&v);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_map_insert_erase);
    RUN_TEST(test_map_copy);
    RUN_TEST(test_amap);
    RUN_TEST(test_map_map);
    RUN_TEST(test_map_iterator);

    return UNITY_END();
}
