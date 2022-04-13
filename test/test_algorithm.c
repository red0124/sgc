#include "test_common.h"
#include <sgc/algorithm.h>
#include <sgc/deque.h>
#include <sgc/fs_unordered_map.h>
#include <sgc/fs_vector.h>
#include <sgc/list.h>
#include <sgc/map.h>
#include <sgc/set.h>
#include <sgc/vector.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT_HEADERS(VECTOR, int, hvector, ITERATE, FIND)
SGC_INIT(VECTOR, int, vector, ITERATE, FIND)

SGC_INIT_HEADERS_DEQUE(int, hdeque)
SGC_INIT_DEQUE(int, deque)

SGC_INIT_HEADERS_FS_PAIR(FS_UNORDERED_MAP, int, int, 100, hfs_map)
SGC_INIT_FS_PAIR(FS_UNORDERED_MAP, int, int, 100, fs_map)

SGC_INIT_HEADERS_FS(FS_VECTOR, int, 100, hfs_vector)
SGC_INIT_FS(FS_VECTOR, int, 100, fs_vector)

void accumulate_sum(const int* const el, void* acc) {
    *(int*)acc += *el;
}

#define SUM(n) ((n) * ((n) + 1) / 2)

void test_accumulate(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, i);
    }

    int sum = 0;
    const int m = TEST_ELEMENTS_NUM;
    vector_accumulate(&v, accumulate_sum, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(m - 1), sum);

    vector_free(&v);
}

int call = 0;

void call_fun(const int* const el) {
    (void)el;
    ++call;
}

void test_foreach(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, i);
    }

    call = 0;
    vector_foreach(&v, call_fun);
    TEST_ASSERT_EQUAL_INT(vector_size(&v), call);

    vector_free(&v);
}

void test_find(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(0, vector_count(&v, i));
        vector_push_back(&v, i);
    }

    struct vector_it it = vector_find_it(&v, -1);
    TEST_ASSERT_EQUAL(vector_it_valid(it), false);
    it = vector_find_it(&v, TEST_ELEMENTS_NUM);
    TEST_ASSERT_EQUAL(vector_it_valid(it), false);

    TEST_ASSERT_EQUAL_INT(NULL, vector_find_el(&v, -1));
    TEST_ASSERT_EQUAL_INT(NULL, vector_find_el(&v, TEST_ELEMENTS_NUM));

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(i, *vector_find_el(&v, i));
        if (i != TEST_ELEMENTS_NUM - 1) {
            it = vector_find_it(&v, i);
            TEST_ASSERT_EQUAL_INT(0, vector_it_eq(it, vector_end(&v)));
        }
        sgc_index index = vector_find_index(&v, i);
        if (index.valid) {
            TEST_ASSERT_EQUAL_INT(i, *vector_at(&v, index.value));
        }
    }

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(1, vector_count(&v, i));
        vector_push_back(&v, i);
        TEST_ASSERT_EQUAL_INT(2, vector_count(&v, i));
        vector_push_back(&v, i);
        TEST_ASSERT_EQUAL_INT(3, vector_count(&v, i));
    }

    vector_free(&v);
}

SGC_INIT_BINARY_FIND(int, vector)

void test_binary_find(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, i);
    }

    TEST_ASSERT_EQUAL_INT(NULL, vector_binary_find_el(&v, -1));
    TEST_ASSERT_EQUAL_INT(NULL, vector_binary_find_el(&v, TEST_ELEMENTS_NUM));

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(i, *vector_binary_find_el(&v, i));
        sgc_index index = vector_binary_find_index(&v, i);
        TEST_ASSERT_EQUAL_INT(i, *vector_at(&v, index.value));
    }

    vector_free(&v);
}

SGC_INIT_QSORT(int, vector)

int compare_reverse(const void* const first, const void* const second) {
    return *(int*)second - *(int*)first;
}

void test_sort(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, i % TEST_ELEMENTS_NUM / 4);
    }

    vector_sort(&v, NULL);

    for (size_t i = 1; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(1, *vector_at(&v, i - 1) <= *vector_at(&v, i));
    }

    vector_sort(&v, compare_reverse);

    for (size_t i = 1; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(1, *vector_at(&v, i) <= *vector_at(&v, i - 1));
    }

    vector_free(&v);
}

SGC_INIT_PAIR(MAP, int, int, map, ITERATE)

void accumulate_sum_pair(const struct map_pair* const p, void* acc) {
    *(int*)acc += p->value;
}

void test_accumulate_map(void) {
    map m;
    map_init(&m);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        map_set(&m, i, i);
    }

    int sum = 0;
    const int q = TEST_ELEMENTS_NUM;
    map_accumulate(&m, accumulate_sum_pair, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(q - 1), sum);

    map_free(&m);
}

void accumulate_pair(const int* const k, const int* const v, void* arg) {
    *(int*)arg += *k + *v * 2;
}

void foreach_pair(const struct map_pair* const m) {
    (void)m;
    ++call;
}

void test_foreach_map(void) {
    map m;
    map_init(&m);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        map_set(&m, i, i);
    }

    call = 0;
    map_foreach(&m, foreach_pair);
    TEST_ASSERT_EQUAL_INT(map_size(&m), call);

    map_free(&m);
}

void test_for_each(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, i);
    }

    for_each(i IN v AS vector) {
        *i += 1;
    }

    size_t j = 1;
    for_each(i IN v AS vector) {
        TEST_ASSERT_EQUAL_INT(*i, j);
        ++j;
    }

    vector_free(&v);
}

void test_for_each_reverse(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, i);
    }

    for_each_reverse(i IN v AS vector) {
        *i += 1;
    }

    size_t j = TEST_ELEMENTS_NUM;
    for_each_reverse(i IN v AS vector) {
        TEST_ASSERT_EQUAL_INT(*i, j);
        --j;
    }

    vector_free(&v);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_accumulate);
    RUN_TEST(test_foreach);
    RUN_TEST(test_find);
    RUN_TEST(test_binary_find);
    RUN_TEST(test_sort);
    RUN_TEST(test_accumulate_map);
    RUN_TEST(test_foreach_map);
    RUN_TEST(test_for_each);
    RUN_TEST(test_for_each_reverse);

    return UNITY_END();
}
