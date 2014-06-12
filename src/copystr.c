
#include "private.h"

char* cstr_copy(const char* data, size_t len)
{
    size_t realsz;
    char* buf;
    realsz = cstr_length(data);
    if(len < realsz)
    {
        realsz = len;
    }
    if((buf = (char*)cstr_allocate(realsz + 1)) == NULL)
    {
        return NULL;
    }
    memcpy(buf, data, realsz);
    buf[realsz] = 0;
    return buf;
}
