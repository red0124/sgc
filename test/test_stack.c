#include "test_common.h"
#include <sgc/stack.h>

SGC_INIT_STACK(int, stack)

void test_stack_push_pop_combinations(void) {
    TEST_PUSH_POP_COMBINATIONS_STACK(stack);
}

SGC_INIT_STACK(oint, ostack)

void test_stack_push_pop_combinations_observed(void) {
    TEST_PUSH_POP_COMBINATIONS_STACK(ostack);
    ASSERT_ALLOCATION_COUNT
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stack_push_pop_combinations);
    RUN_TEST(test_stack_push_pop_combinations_observed);

    disable_allocation();
    RUN_TEST(test_stack_push_pop_combinations);
    RUN_TEST(test_stack_push_pop_combinations_observed);
    return UNITY_END();
}
