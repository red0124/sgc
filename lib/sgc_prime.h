#pragma once

static inline size_t sgc_sqrt(size_t n)
{
        size_t i = 1;
        while(i * i <= n)
        {
                ++i;
        }
        return i;
}

static inline int sgc_is_prime(size_t n)
{
        int is_prime = 1;
        for(size_t i = 2; i <= sgc_sqrt(n); ++i)
        {
                if(n % i == 0)
                {
                        is_prime = 0;
                        break;
                }
        }
        return is_prime;
}

static inline size_t sgc_next_prime(size_t n)
{
        while(!sgc_is_prime(n))
        {
                ++n;
        }
        return n;
}
