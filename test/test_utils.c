#include "test_common.h"
#include <sgc/algorithm.h>
#include <sgc/vector.h>

struct foo {
    uint32_t i;
    uint32_t j;
};

SGC_INIT_PRIMITIVE_STRUCT(struct foo, foo)

static void test_struct_generator_without_padding(void) {
    foo f;
    foo_init(&f);

    foo f2;
    foo_init(&f2);

    f2.i = 1;
    f2.j = 2;

    ASSERT_NOT_EQUAL(f.i, f2.i);
    ASSERT_NOT_EQUAL(f.j, f2.j);

    foo_copy(&f, &f2);
    ASSERT_EQUAL(f.i, f2.i);
    ASSERT_EQUAL(f.j, f2.j);

    foo_free(&f2);
    foo_free(&f);
}

struct bar {
    uint8_t i;
    uint32_t j;
};

SGC_INIT_PRIMITIVE_STRUCT(struct bar, bar)

static void test_struct_generator_with_padding(void) {
    bar b;
    bar_init(&b);

    bar b2;
    bar_init(&b2);

    b2.i = 1;
    b2.j = 2;

    ASSERT_NOT_EQUAL(b.i, b2.i);
    ASSERT_NOT_EQUAL(b.j, b2.j);

    bar_copy(&b, &b2);
    ASSERT_EQUAL(b.i, b2.i);
    ASSERT_EQUAL(b.j, b2.j);

    bar_free(&b2);
    bar_free(&b);
}

struct tar {
    uint32_t i;
    uint8_t array[5];
};

SGC_INIT_PRIMITIVE_STRUCT(struct tar, tar)

static void test_struct_with_array(void) {
    tar t;
    tar_init(&t);

    tar t2;
    tar_init(&t2);

    t2.i = 10;
    memset(t2.array, 'x', sizeof(t2.array));

    ASSERT_NOT_EQUAL(t.i, t2.i);
    for (size_t i = 0; i < sizeof(t.array) / sizeof(uint8_t); ++i) {
        ASSERT_NOT_EQUAL(t.array[i], t2.array[i]);
    }

    tar_copy(&t, &t2);

    ASSERT_EQUAL(t.i, t2.i);
    for (size_t i = 0; i < sizeof(t.array) / sizeof(uint8_t); ++i) {
        ASSERT_EQUAL(t.array[i], t2.array[i]);
    }

    tar_free(&t2);
    tar_free(&t);
}

SGC_INIT(VECTOR, tar, vec)

static void test_vector_of_structs(void) {
    vec v;
    vec_init(&v);

    tar t;
    tar_init(&t);

    t.i = 10;
    memset(t.array, 'x', sizeof(t.array));
    vec_push_back(&v, t);
    ASSERT_EQUAL(t.i, vec_back(&v)->i);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(t.array, vec_back(&v)->array, 5);


    t.i = 11;
    memset(t.array, 'y', sizeof(t.array));
    vec_push_back(&v, t);
    ASSERT_EQUAL(t.i, vec_back(&v)->i);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(t.array, vec_back(&v)->array, 5);

    t.i = 12;
    memset(t.array, 'z', sizeof(t.array));
    vec_push_back(&v, t);
    ASSERT_EQUAL(t.i, vec_back(&v)->i);
    TEST_ASSERT_EQUAL_UINT8_ARRAY(t.array, vec_back(&v)->array, 5);

    ASSERT_EQUAL(3, vec_size(&v));
    ASSERT_EQUAL(10, vec_at(&v, 0)->i);
    ASSERT_EQUAL(11, vec_at(&v, 1)->i);
    ASSERT_EQUAL(12, vec_at(&v, 2)->i);

    TEST_ASSERT_EQUAL_UINT8_ARRAY("xxxxx", vec_at(&v, 0)->array, 5);
    TEST_ASSERT_EQUAL_UINT8_ARRAY("yyyyy", vec_at(&v, 1)->array, 5);
    TEST_ASSERT_EQUAL_UINT8_ARRAY("zzzzz", vec_at(&v, 2)->array, 5);

    vec_free(&v);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_struct_generator_without_padding);
    RUN_TEST(test_struct_generator_with_padding);
    RUN_TEST(test_struct_with_array);
    RUN_TEST(test_vector_of_structs);
    return UNITY_END();
}
