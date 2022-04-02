#include "test_common.h"
#include <sgc/algorithm.h>
#include <sgc/deque.h>
#include <sgc/list.h>
#include <sgc/map.h>
#include <sgc/set.h>
#include <sgc/static_unordered_map.h>
#include <sgc/vector.h>

#define TEST_ELEMENTS_NUM 50

SGC_INIT(VECTOR, int, vector, ITERATE, FIND, FIND_ITERATOR)
SGC_INIT_DEQUE(int, deque)

    /*
void fold_sum(const int* const el, void* acc) {
    *(int*)acc += *el;
}

#define SUM(n) ((n) * ((n) + 1) / 2)

void test_fold(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, i);
    }

    int sum = 0;
    const int m = TEST_ELEMENTS_NUM;
    vector_fold(&v, fold_sum, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(m - 1), sum);

    sum = 0;
    vector_fold_reverse(&v, fold_sum, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(m - 1), sum);

    sum = 0;
    const int n = 10;
    vector_fold_range(vector_begin(&v), vector_from(&v, n), fold_sum, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(n), sum);

    sum = 0;
    vector_fold_range_reverse(vector_begin(&v), vector_from(&v, n), fold_sum,
                              &sum);
    TEST_ASSERT_EQUAL_INT(SUM(n), sum);

    const int o = 5;
    sum = 0;
    vector_fold_range(vector_from(&v, o), vector_from(&v, n), fold_sum, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(n) - SUM(o - 1), sum);

    sum = 0;
    vector_fold_range_reverse(vector_from(&v, o), vector_from(&v, n), fold_sum,
                              &sum);
    TEST_ASSERT_EQUAL_INT(SUM(n) - SUM(o - 1), sum);

    vector_free(&v);
}

int call = 0;

void execute(const int* const el) {
    (void)el;
    ++call;
}

void test_execute(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, i);
    }

    call = 0;
    vector_execute(&v, execute);
    TEST_ASSERT_EQUAL_INT(vector_size(&v), call);

    call = 0;
    vector_execute_reverse(&v, execute);
    TEST_ASSERT_EQUAL_INT(vector_size(&v), call);

    call = 0;
    const int n = 10;
    vector_execute_range(vector_begin(&v), vector_from(&v, n), execute);
    TEST_ASSERT_EQUAL_INT(n + 1, call);

    call = 0;
    vector_execute_range_reverse(vector_begin(&v), vector_from(&v, n), execute);
    TEST_ASSERT_EQUAL_INT(n + 1, call);

    const int o = 5;
    call = 0;
    vector_execute_range(vector_from(&v, o), vector_from(&v, n), execute);
    TEST_ASSERT_EQUAL_INT(n - o + 1, call);

    call = 0;
    vector_execute_range_reverse(vector_from(&v, o), vector_from(&v, n),
                                 execute);
    TEST_ASSERT_EQUAL_INT(n - o + 1, call);

    vector_free(&v);
}

void test_find(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(0, vector_count(&v, i));
        vector_push_back(&v, i);
    }

    struct vector_it it = vector_find(&v, -1);
    TEST_ASSERT_EQUAL_INT(1, vector_it_equal(it, vector_end(&v)));
    it = vector_find(&v, TEST_ELEMENTS_NUM);
    TEST_ASSERT_EQUAL_INT(1, vector_it_equal(it, vector_end(&v)));

    TEST_ASSERT_EQUAL_INT(NULL, vector_find_el(&v, -1));
    TEST_ASSERT_EQUAL_INT(NULL, vector_find_el(&v, TEST_ELEMENTS_NUM));

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        TEST_ASSERT_EQUAL_INT(i, *vector_find_el(&v, i));
        if (i != TEST_ELEMENTS_NUM - 1) {
            it = vector_find(&v, i);
            TEST_ASSERT_EQUAL_INT(0, vector_it_equal(it, vector_end(&v)));
        }
        ssize_t index = vector_find_index(&v, i);
        if (index >= 0) {
            TEST_ASSERT_EQUAL_INT(i, *vector_at(&v, index));
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
        TEST_ASSERT_EQUAL_INT(i,
                              *vector_at(&v, vector_binary_find_index(&v, i)));
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

SGC_INIT_PAIR(MAP, int, int, map, ITERATE, ITERATE_PAIR)

void fold_sum_pair(const struct map_pair* const p, void* acc) {
    *(int*)acc += p->value;
}

void test_fold_map(void) {
    map m;
    map_init(&m);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        map_set(&m, i, i);
    }

    int sum = 0;
    const int q = TEST_ELEMENTS_NUM;
    map_fold(&m, fold_sum_pair, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(q - 1), sum);

    sum = 0;
    map_fold_reverse(&m, fold_sum_pair, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(q - 1), sum);

    sum = 0;
    map_fold_range_reverse(map_begin(&m), map_end(&m), fold_sum_pair, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(q - 1), sum);

    sum = 0;
    map_fold_range(map_begin(&m), map_end(&m), fold_sum_pair, &sum);
    TEST_ASSERT_EQUAL_INT(SUM(q - 1), sum);

    map_free(&m);
}

void fold_pair(const int* const k, const int* const v, void* arg) {
    *(int*)arg += *k + *v * 2;
}

void execute_pair(const struct map_pair* const m) {
    (void)m;
    ++call;
}

void test_execute_map(void) {
    map m;
    map_init(&m);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        map_set(&m, i, i);
    }

    call = 0;
    map_execute(&m, execute_pair);
    TEST_ASSERT_EQUAL_INT(map_size(&m), call);

    call = 0;
    map_execute_reverse(&m, execute_pair);
    TEST_ASSERT_EQUAL_INT(map_size(&m), call);

    call = 0;
    map_execute_range(map_begin(&m), map_end(&m), execute_pair);
    TEST_ASSERT_EQUAL_INT(map_size(&m), call);

    call = 0;
    map_execute_range_reverse(map_begin(&m), map_end(&m), execute_pair);
    TEST_ASSERT_EQUAL_INT(map_size(&m), call);

    map_free(&m);
}

void test_for_each1(void) {
    vector v;
    vector_init(&v);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, i);
    }

    sgc_for_each(i, v, vector) {
        *i += 1;
    }

    size_t j = 1;
    sgc_for_each(i, v, vector) {
        TEST_ASSERT_EQUAL_INT(*i, j);
        ++j;
    }

    vector_free(&v);
}

void test_for_each2(void) {
    vector v1;
    vector v2;
    vector_init(&v1);
    vector_init(&v2);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v1, i);
        vector_push_back(&v2, 2 * i);
    }

    sgc_for_each(i, v1, vector, v2, vector) {
        *i.first += 1;
        *i.second += 2;
    }

    size_t j = 1;
    sgc_for_each(i, v1, vector) {
        TEST_ASSERT_EQUAL_INT(*i, j);
        ++j;
    }

    j = 2;
    sgc_for_each(i, v2, vector) {
        TEST_ASSERT_EQUAL_INT(*i, j);
        j += 2;
    }

    sgc_for_each(i, v1, vector, v2, vector) {
        TEST_ASSERT_EQUAL_INT(*i.first * 2, *i.second);
        j += 2;
    }

    vector_free(&v1);
    vector_free(&v2);
}

SGC_INIT(DEQUE, char, cdeq)

void test_for_each3(void) {
    vector v;
    vector_init(&v);

    map m;
    map_init(&m);

    cdeq d;
    cdeq_init(&d);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v, 0);
        map_set(&m, i, 0);
        cdeq_push_back(&d, '0');
    }

    int j = 0;
    sgc_for_each(i, v, vector, m, map, d, cdeq) {
        TEST_ASSERT_EQUAL_INT(*i.first, 0);
        TEST_ASSERT_EQUAL_INT(i.second->key, j);
        TEST_ASSERT_EQUAL_INT(i.second->value, 0);
        TEST_ASSERT_EQUAL_INT(*i.third, '0');
        ++j;
    }

    TEST_ASSERT_EQUAL_INT(j, TEST_ELEMENTS_NUM);

    sgc_for_each_reverse(i, v, vector, m, map, d, cdeq) {
        --j;
        TEST_ASSERT_EQUAL_INT(*i.first, 0);
        TEST_ASSERT_EQUAL_INT(i.second->key, j);
        TEST_ASSERT_EQUAL_INT(i.second->value, 0);
        TEST_ASSERT_EQUAL_INT(*i.third, '0');
    }

    TEST_ASSERT_EQUAL_INT(j, 0);

    vector_free(&v);
    map_free(&m);
    cdeq_free(&d);
}

void test_for_each_intersect(void) {
    vector v1, v2;
    vector_init(&v1);
    vector_init(&v2);

    for (size_t i = 0; i < TEST_ELEMENTS_NUM; ++i) {
        vector_push_back(&v1, i);
        vector_push_back(&v1, TEST_ELEMENTS_NUM - i);
    }

    sgc_for_each_intersect(i, v1, v2, vector) {
        TEST_ASSERT_EQUAL_INT(*i.first, *i.second);
    }

    vector_free(&v2);
    vector_free(&v1);
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_fold);
    RUN_TEST(test_execute);
    RUN_TEST(test_find);
    RUN_TEST(test_binary_find);
    RUN_TEST(test_sort);
    RUN_TEST(test_fold_map);
    RUN_TEST(test_execute_map);
    RUN_TEST(test_for_each1);
    RUN_TEST(test_for_each2);
    RUN_TEST(test_for_each3);
    RUN_TEST(test_for_each_intersect);

    return UNITY_END();
}
    */
