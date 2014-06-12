
#include "private.h"

char* cstr_substr(const char* inpstr, size_t inlen, size_t startpos, size_t slen)
{
    char* buf;
    if(slen == 0)
    {
        assert(slen == 0);
        return NULL;
    }
    if(startpos > slen)
    {
        assert(startpos > slen);
        return NULL;
    }
    if((startpos == 0) && (inlen == slen))
    {
        dbg("startpos is 0 and inlen == slen, cstr_copy()ing $inpstr\n");
        return cstr_copy(inpstr, inlen);
    }
    if((buf = (char*)cstr_allocate(slen + 1)) == NULL)
    {
        return NULL;
    }
    strncpy(buf, inpstr + startpos, slen);
    buf[slen] = 0;
    return buf;
}
