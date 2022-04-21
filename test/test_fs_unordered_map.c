#include "test_common.h"
#include <sgc/fs_unordered_map.h>

#define GENERATE_FS_UNORDERED_MAP_TESTS(S)                                     \
    SGC_INIT_FS_UNORDERED_MAP(int, int, S, map##S)                             \
                                                                               \
    void test_fs_unordered_map_insert_erase_combinations##S(void) {            \
        TEST_INSERT_ERASE_COMBINATIONS_MAP_MAX(map##S, S);                     \
    }                                                                          \
                                                                               \
    SGC_INIT_FS_UNORDERED_MAP(oint, oint, S, omap##S)                          \
                                                                               \
    void test_fs_unordered_map_insert_erase_combinations_observed##S(void) {   \
        TEST_INSERT_ERASE_COMBINATIONS_MAP_MAX(omap##S, S);                    \
        ASSERT_ALLOCATION_COUNT                                                \
    }                                                                          \
                                                                               \
    SGC_INIT_FS_UNORDERED_MAP(oint, int, S, oint_int_map##S)                   \
                                                                               \
    void test_fs_unordered_map_insert_erase_combinations_observed_key##S(      \
        void) {                                                                \
        TEST_INSERT_ERASE_COMBINATIONS_MAP_MAX(oint_int_map##S, S);            \
        ASSERT_ALLOCATION_COUNT                                                \
    }                                                                          \
                                                                               \
    SGC_INIT_FS_UNORDERED_MAP(int, oint, S, int_oint_map##S)                   \
                                                                               \
    void test_fs_unordered_map_insert_erase_combinations_observed_value##S(    \
        void) {                                                                \
        TEST_INSERT_ERASE_COMBINATIONS_MAP_MAX(int_oint_map##S, S);            \
        ASSERT_ALLOCATION_COUNT                                                \
    }

GENERATE_FS_UNORDERED_MAP_TESTS(1)
GENERATE_FS_UNORDERED_MAP_TESTS(2)
GENERATE_FS_UNORDERED_MAP_TESTS(3)
GENERATE_FS_UNORDERED_MAP_TESTS(4)
GENERATE_FS_UNORDERED_MAP_TESTS(5)
GENERATE_FS_UNORDERED_MAP_TESTS(6)
GENERATE_FS_UNORDERED_MAP_TESTS(256)

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations1);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed1);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key1);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value1);

    RUN_TEST(test_fs_unordered_map_insert_erase_combinations2);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed2);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key2);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value2);

    RUN_TEST(test_fs_unordered_map_insert_erase_combinations3);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed3);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key3);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value3);

    RUN_TEST(test_fs_unordered_map_insert_erase_combinations4);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed4);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key4);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value4);

    RUN_TEST(test_fs_unordered_map_insert_erase_combinations5);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed5);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key5);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value5);

    RUN_TEST(test_fs_unordered_map_insert_erase_combinations6);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed6);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key6);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value6);

    RUN_TEST(test_fs_unordered_map_insert_erase_combinations256);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed256);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key256);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value256);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations256);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed256);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key256);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value256);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations256);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed256);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_key256);
    RUN_TEST(test_fs_unordered_map_insert_erase_combinations_observed_value256);
    return UNITY_END();
}
