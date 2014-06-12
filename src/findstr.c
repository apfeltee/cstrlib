
#include "private.h"

bool cstr_find_string(
    const char* inpstr,
    size_t ibegin,
    size_t iend,
    const char* findme,
    size_t findlen,
    size_t* res)
{
    size_t j;
    size_t realpos;
    bool found;
    if(findlen == 0)
    {
        (*res) = ibegin;
        return true;
    }
    for((*res) = ibegin; (*res) < iend; (*res)++)
    {
        if(inpstr[*res] == findme[0])
        {
            realpos = (*res);
            for(j=0; j<findlen; j++)
            {
                found = true;
                if(inpstr[(*res) + j] != findme[j])
                {
                    found = false;
                    break;
                }
            }
            if(found == true)
            {
                (*res) = realpos;
                return true;
            }
        }
    }
    return false;
}

