
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cstrlib.h"

//#define DEBUG

#if defined(DEBUG)
#   include <assert.h>
#   define dbg(...) \
        do { \
            fprintf(stderr, "*** dbg [%s:%d] ", \
                __FUNCTION__, __LINE__); \
            fprintf(stderr, __VA_ARGS__); \
        } while(0);
#   define cstr_allocate(size) \
        cstr_mem_check_alloc(size, __FILE__, __FUNCTION__, __LINE__)
#   define cstr_reallocate(ptr, size) \
        cstr_mem_check_realloc(ptr, size, __FILE__, __FUNCTION__, __LINE__)
#else
#   define assert(...)
#   define dbg(...)
#   define cstr_allocate(size) cstr_mem_alloc(size)
#   define cstr_reallocate(ptr, size) cstr_mem_realloc(ptr, size)
#endif

typedef int(*cstr_charfunc_t)(int);

void* cstr_mem_alloc(size_t len);

void cstr_mem_free(void* ptr);

void* cstr_mem_check_alloc(
    size_t len,
    const char* cnfile,
    const char* cnfunc,
    int cnline
);

char* cstr_util_modify_inplace(char* inbuf, size_t len, cstr_charfunc_t fn);