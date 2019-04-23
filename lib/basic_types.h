#pragma once

#include "static_types.h"

#ifndef SGC_NO_BASIC_TYPES
#ifndef SGC_BASIC_TYPES_HEADERS
#ifndef SGC_BASIC_TYPES_EXTERN
SGC_INIT_BASIC_TYPE(char, char, static);
SGC_INIT_BASIC_TYPE(unsigned char, unsigned_char, static);
SGC_INIT_BASIC_TYPE(short, short, static);
SGC_INIT_BASIC_TYPE(unsigned short, unsigned_short, static);
SGC_INIT_BASIC_TYPE(int, int, static);
SGC_INIT_BASIC_TYPE(unsigned int, unsigned_int, static);
SGC_INIT_BASIC_TYPE(long, long, static);
SGC_INIT_BASIC_TYPE(unsigned long, unsigned_long, static);
SGC_INIT_BASIC_TYPE(float, float, static);
SGC_INIT_BASIC_TYPE(double, double, static);
SGC_INIT_BASIC_TYPE(long double, long_double, static);

SGC_INIT_BASIC_HASH(char, char, static);
SGC_INIT_BASIC_HASH(unsigned char, unsigned_char, static);
SGC_INIT_BASIC_HASH(short, short, static);
SGC_INIT_BASIC_HASH(unsigned short, unsigned_short, static);
SGC_INIT_BASIC_HASH(int, int, static);
SGC_INIT_BASIC_HASH(unsigned int, unsigned_int, static);
SGC_INIT_BASIC_HASH(long, long, static);
SGC_INIT_BASIC_HASH(unsigned long, unsigned_long, static);
#else
SGC_INIT_BASIC_TYPE(char, char, extern);
SGC_INIT_BASIC_TYPE(unsigned char, unsigned_char, extern);
SGC_INIT_BASIC_TYPE(short, short, extern);
SGC_INIT_BASIC_TYPE(unsigned short, unsigned_short, extern);
SGC_INIT_BASIC_TYPE(int, int, extern);
SGC_INIT_BASIC_TYPE(unsigned int, unsigned_int, extern);
SGC_INIT_BASIC_TYPE(long, long, extern);
SGC_INIT_BASIC_TYPE(unsigned long, unsigned_long, extern);
SGC_INIT_BASIC_TYPE(float, float, extern);
SGC_INIT_BASIC_TYPE(double, double, extern);
SGC_INIT_BASIC_TYPE(long double, long_double, extern);

SGC_INIT_BASIC_HASH(char, char, static);
SGC_INIT_BASIC_HASH(unsigned char, unsigned_char, static);
SGC_INIT_BASIC_HASH(short, short, static);
SGC_INIT_BASIC_HASH(unsigned short, unsigned_short, static);
SGC_INIT_BASIC_HASH(int, int, static);
SGC_INIT_BASIC_HASH(unsigned int, unsigned_int, static);
SGC_INIT_BASIC_HASH(long, long, static);
SGC_INIT_BASIC_HASH(unsigned long, unsigned_long, static);
#endif
#else

SGC_INIT_HEADERS_BASIC_TYPE(char, char, extern );
SGC_INIT_HEADERS_BASIC_TYPE(unsigned char, unsigned_char, extern);
SGC_INIT_HEADERS_BASIC_TYPE(short, short, extern);
SGC_INIT_HEADERS_BASIC_TYPE(unsigned short, unsigned_short, extern);
SGC_INIT_HEADERS_BASIC_TYPE(int, int, extern);
SGC_INIT_HEADERS_BASIC_TYPE(unsigned int, unsigned_int, extern);
SGC_INIT_HEADERS_BASIC_TYPE(long, long, extern);
SGC_INIT_HEADERS_BASIC_TYPE(unsigned long, unsigned_long, extern);
SGC_INIT_HEADERS_BASIC_TYPE(float, float, extern);
SGC_INIT_HEADERS_BASIC_TYPE(double, double, extern);
SGC_INIT_HEADERS_BASIC_TYPE(long double, long_double, extern);

SGC_INIT_HEADERS_BASIC_HASH(char, char, extern);
SGC_INIT_HEADERS_BASIC_HASH(unsigned char, unsigned_char, extern);
SGC_INIT_HEADERS_BASIC_HASH(short, short, extern);
SGC_INIT_HEADERS_BASIC_HASH(unsigned short, unsigned_short, extern);
SGC_INIT_HEADERS_BASIC_HASH(int, int, extern);
SGC_INIT_HEADERS_BASIC_HASH(unsigned int, unsigned_int, extern);
SGC_INIT_HEADERS_BASIC_HASH(long, long, extern);
SGC_INIT_HEADERS_BASIC_HASH(unsigned long, unsigned_long, extern);
#endif
#endif
