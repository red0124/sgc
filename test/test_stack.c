#include "test_common.h"
#include <sgc/stack.h>

SGC_INIT_STACK(int, stack)

void test_stack_push_pop_combinations(void) {
    TEST_TSTK(stack);
}

SGC_INIT_STACK(oint, ostack)

void test_stack_push_pop_combinations_observed(void) {
    TEST_TSTK(ostack);
    TEST_ASSERT_GREATER_THAN(0, oint_allocation_count);
    ASSERT_EQUAL(oint_allocation_count, oint_deallocation_count);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stack_push_pop_combinations);
    RUN_TEST(test_stack_push_pop_combinations_observed);
    return UNITY_END();
}
