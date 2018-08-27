#define INIT_STATIC(T, N)                                                      \
                                                                               \
        void N##_init(T *el)                                                   \
        {                                                                      \
                *el = 0;                                                       \
        }                                                                      \
                                                                               \
        void N##_free(T *el)                                                   \
        {                                                                      \
                (void)el;                                                      \
        }                                                                      \
                                                                               \
        void N##_copy(T *dst, const T *const src)                              \
        {                                                                      \
                *dst = *src;                                                   \
        }                                                                      \
                                                                               \
        int N##_equal(const T *const first, const T *const second)             \
        {                                                                      \
                return *first == *second;                                      \
        }                                                                      \
                                                                               \
        int N##_compare(const T *const first, const T *const second)           \
        {                                                                      \
                return (int)(*first - *second);                                \
        }                                                                      \
                                                                               \
        int N##_void_compare(const void *const first, const void *const second)\
        {                                                                      \
                return (int)(*(T*)first - *(T*)second);                        \
        }                                                                      \
                                                                               \
        int N##_is_static()                                                    \
        {                                                                      \
                return 1;                                                      \
        }

INIT_STATIC(char, char);
INIT_STATIC(signed char, signed_char);
INIT_STATIC(unsigned char, unsigned_char);
INIT_STATIC(short, short);
INIT_STATIC(short int, short_int);
INIT_STATIC(signed short, signed_short);
INIT_STATIC(signed short int, signed_short_int);
INIT_STATIC(unsigned short, unsigned_short);
INIT_STATIC(unsigned short int, unsigned_short_int);
INIT_STATIC(int, int);
INIT_STATIC(signed int, signed_int);
INIT_STATIC(signed, signed);
INIT_STATIC(unsigned int, unsigned_int);
INIT_STATIC(unsigned, unsigned);
INIT_STATIC(long, long);
INIT_STATIC(long int, long_int);
INIT_STATIC(signed long, signed_long);
INIT_STATIC(signed long int, signed_long_int);
INIT_STATIC(unsigned long int, unsigned_long_int);
INIT_STATIC(unsigned long, unsigned_long);
INIT_STATIC(long long, long_long);
INIT_STATIC(long long int, long_long_int);
INIT_STATIC(signed long long, signed_long_long);
INIT_STATIC(signed long long int, signed_long_long_int);
INIT_STATIC(unsigned long long, unsigned_long_long);
INIT_STATIC(unsigned long long int, unsigned_long_long_int);
INIT_STATIC(float, float);
INIT_STATIC(double, double);
INIT_STATIC(long double, long_double);
INIT_STATIC(float _Complex, float_complex);
INIT_STATIC(double _Complex, double_complex);
INIT_STATIC(long double _Complex, long_double_complex);
