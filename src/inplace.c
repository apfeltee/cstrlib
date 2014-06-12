
#include "private.h"

char* cstr_toupper(char* inbuf, size_t len)
{
    return cstr_util_modify_inplace(inbuf, len, toupper);
}

char* cstr_tolower(char* inbuf, size_t len)
{
    return cstr_util_modify_inplace(inbuf, len, tolower);
}


