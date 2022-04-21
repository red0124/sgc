#include "test_common.h"
#include <sgc/fs_priority_queue.h>

#define GENERATE_FS_PRIORITY_QUEUE_TESTS(S)                                    \
    SGC_INIT_FS_PRIORITY_QUEUE(int, S, priority_queue##S)                      \
                                                                               \
    void test_fs_priority_queue_push_pop_combinations##S(void) {               \
        TEST_PUSH_POP_COMBINATIONS_PRIORITY_QUEUE_MAX(priority_queue##S, S);   \
    }                                                                          \
                                                                               \
    SGC_INIT_FS_PRIORITY_QUEUE(oint, S, opriority_queue##S)                    \
                                                                               \
    void test_fs_priority_queue_push_pop_combinations_observed##S(void) {      \
        TEST_PUSH_POP_COMBINATIONS_PRIORITY_QUEUE_MAX(opriority_queue##S, S);  \
        ASSERT_ALLOCATION_COUNT                                                \
    }

GENERATE_FS_PRIORITY_QUEUE_TESTS(1)
GENERATE_FS_PRIORITY_QUEUE_TESTS(2)
GENERATE_FS_PRIORITY_QUEUE_TESTS(3)
GENERATE_FS_PRIORITY_QUEUE_TESTS(4)
GENERATE_FS_PRIORITY_QUEUE_TESTS(5)
GENERATE_FS_PRIORITY_QUEUE_TESTS(6)
GENERATE_FS_PRIORITY_QUEUE_TESTS(256)

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_fs_priority_queue_push_pop_combinations1);
    RUN_TEST(test_fs_priority_queue_push_pop_combinations_observed1);

    RUN_TEST(test_fs_priority_queue_push_pop_combinations2);
    RUN_TEST(test_fs_priority_queue_push_pop_combinations_observed2);

    RUN_TEST(test_fs_priority_queue_push_pop_combinations3);
    RUN_TEST(test_fs_priority_queue_push_pop_combinations_observed3);

    RUN_TEST(test_fs_priority_queue_push_pop_combinations4);
    RUN_TEST(test_fs_priority_queue_push_pop_combinations_observed4);

    RUN_TEST(test_fs_priority_queue_push_pop_combinations5);
    RUN_TEST(test_fs_priority_queue_push_pop_combinations_observed5);

    RUN_TEST(test_fs_priority_queue_push_pop_combinations6);
    RUN_TEST(test_fs_priority_queue_push_pop_combinations_observed6);

    RUN_TEST(test_fs_priority_queue_push_pop_combinations256);
    RUN_TEST(test_fs_priority_queue_push_pop_combinations_observed256);

    enable_allocation();
    enable_moveing();
    RUN_TEST(test_fs_priority_queue_push_pop_combinations256);
    RUN_TEST(test_fs_priority_queue_push_pop_combinations_observed256);

    disable_moveing();
    enable_sharing();
    RUN_TEST(test_fs_priority_queue_push_pop_combinations256);
    RUN_TEST(test_fs_priority_queue_push_pop_combinations_observed256);
    return UNITY_END();
}
