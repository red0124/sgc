#pragma once

static inline size_t sgc_exp_two(size_t curr)
{
        size_t power = 1;
        for(size_t i = 0; i < curr; ++i)
        {
                power *= 2;
        }
        return power;
}

static inline size_t sgc_log_two(size_t size)
{
        size_t curr = 1;
        while(size >= sgc_exp_two(curr))
        {
                ++curr;
        }
        return curr + 1;
}
