#include "test_common.h"
#include <sgc/fs_stack.h>

#define GENERATE_FS_STACK_TESTS(S)                                             \
    SGC_INIT_FS_STACK(int, S, stack##S)                                        \
                                                                               \
    void test_fs_stack_push_pop_combinations##S(void) {                        \
        TEST_PUSH_POP_COMBINATIONS_STACK_MAX(stack##S, S);                     \
    }                                                                          \
                                                                               \
    SGC_INIT_FS_STACK(oint, S, ostack##S)                                      \
                                                                               \
    void test_fs_stack_push_pop_combinations_observed##S(void) {               \
        TEST_PUSH_POP_COMBINATIONS_STACK_MAX(ostack##S, S);                    \
        ASSERT_ALLOCATION_COUNT                                                \
    }

GENERATE_FS_STACK_TESTS(1)
GENERATE_FS_STACK_TESTS(2)
GENERATE_FS_STACK_TESTS(3)
GENERATE_FS_STACK_TESTS(4)
GENERATE_FS_STACK_TESTS(5)
GENERATE_FS_STACK_TESTS(6)
GENERATE_FS_STACK_TESTS(256)

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_stack_push_pop_combinations1);
    RUN_TEST(test_fs_stack_push_pop_combinations_observed1);

    RUN_TEST(test_fs_stack_push_pop_combinations2);
    RUN_TEST(test_fs_stack_push_pop_combinations_observed2);

    RUN_TEST(test_fs_stack_push_pop_combinations3);
    RUN_TEST(test_fs_stack_push_pop_combinations_observed3);

    RUN_TEST(test_fs_stack_push_pop_combinations4);
    RUN_TEST(test_fs_stack_push_pop_combinations_observed4);

    RUN_TEST(test_fs_stack_push_pop_combinations5);
    RUN_TEST(test_fs_stack_push_pop_combinations_observed5);

    RUN_TEST(test_fs_stack_push_pop_combinations6);
    RUN_TEST(test_fs_stack_push_pop_combinations_observed6);

    RUN_TEST(test_fs_stack_push_pop_combinations256);
    RUN_TEST(test_fs_stack_push_pop_combinations_observed256);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_fs_stack_push_pop_combinations256);
    RUN_TEST(test_fs_stack_push_pop_combinations_observed256);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_fs_stack_push_pop_combinations256);
    RUN_TEST(test_fs_stack_push_pop_combinations_observed256);
    return UNITY_END();
}
