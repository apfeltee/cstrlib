
#include "private.h"

bool cstr_find_char(const char* inpstr, size_t ibegin, size_t iend, int findme, size_t* res)
{
    for((*res)=ibegin; (*res) < iend; (*res)++)
    {
        if(inpstr[*res] == findme)
        {
            return true;
        }
    }
    return false;
}
