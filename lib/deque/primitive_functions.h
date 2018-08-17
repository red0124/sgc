#define INIT_ELEMENT_FUNCTIONS(T, N)                                           \
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

INIT_ELEMENT_FUNCTIONS(char, char);
INIT_ELEMENT_FUNCTIONS(signed char, signed_char);
INIT_ELEMENT_FUNCTIONS(unsigned char, unsigned_char);
INIT_ELEMENT_FUNCTIONS(short, short);
INIT_ELEMENT_FUNCTIONS(short int, short_int);
INIT_ELEMENT_FUNCTIONS(signed short, signed_short);
INIT_ELEMENT_FUNCTIONS(signed short int, signed_short_int);
INIT_ELEMENT_FUNCTIONS(unsigned short, unsigned_short);
INIT_ELEMENT_FUNCTIONS(unsigned short int, unsigned_short_int);
INIT_ELEMENT_FUNCTIONS(int, int);
INIT_ELEMENT_FUNCTIONS(signed int, signed_int);
INIT_ELEMENT_FUNCTIONS(signed, signed);
INIT_ELEMENT_FUNCTIONS(unsigned int, unsigned_int);
INIT_ELEMENT_FUNCTIONS(unsigned, unsigned);
INIT_ELEMENT_FUNCTIONS(long, long);
INIT_ELEMENT_FUNCTIONS(long int, long_int);
INIT_ELEMENT_FUNCTIONS(signed long, signed_long);
INIT_ELEMENT_FUNCTIONS(signed long int, signed_long_int);
INIT_ELEMENT_FUNCTIONS(unsigned long int, unsigned_long_int);
INIT_ELEMENT_FUNCTIONS(unsigned long, unsigned_long);
INIT_ELEMENT_FUNCTIONS(long long, long_long);
INIT_ELEMENT_FUNCTIONS(long long int, long_long_int);
INIT_ELEMENT_FUNCTIONS(signed long long, signed_long_long);
INIT_ELEMENT_FUNCTIONS(signed long long int, signed_long_long_int);
INIT_ELEMENT_FUNCTIONS(unsigned long long, unsigned_long_long);
INIT_ELEMENT_FUNCTIONS(unsigned long long int, unsigned_long_long_int);
INIT_ELEMENT_FUNCTIONS(float, float);
INIT_ELEMENT_FUNCTIONS(double, double);
INIT_ELEMENT_FUNCTIONS(long double, long_double);
INIT_ELEMENT_FUNCTIONS(float _Complex, float_complex);
INIT_ELEMENT_FUNCTIONS(double _Complex, double_complex);
INIT_ELEMENT_FUNCTIONS(long double _Complex, long_double_complex);
