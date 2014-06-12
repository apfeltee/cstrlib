
#include "private.h"

void* cstr_mem_alloc(size_t len)
{
    return malloc(len);
}

void cstr_mem_free(void* ptr)
{
    free(ptr);
}

void* cstr_mem_check_alloc(
    size_t len,
    const char* cnfile,
    const char* cnfunc,
    int cnline
)
{
    void* p;
    (void)cnfile;
    (void)cnfunc;
    (void)cnline;
    if((p = cstr_mem_alloc(len)) == NULL)
    {
        dbg("cstr_allocate(%d) failed in function '%s', line %d, in file '%s'\n",
            len, cnfunc, cnline, cnfile
        );
        abort();
        return NULL;
    }
    return p;
}

char* cstr_util_modify_inplace(char* inbuf, size_t len, cstr_charfunc_t fn)
{
    size_t ci;
    int chval;
    for(ci=0; ci<len; ci++)
    {
        chval = fn(inbuf[ci]);
        inbuf[ci] = chval;
    }
    return inbuf;
}

