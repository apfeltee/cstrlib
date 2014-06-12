
#include "private.h"

size_t cstr_length(const char* str)
{
    size_t ci;
    if(str != NULL)
    {
        for(ci=0;; ci++)
        {
            if(str[ci] == 0)
            {
                return ci;
            }
        }
    }
    return 0;
}
