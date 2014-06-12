
#include "private.h"

size_t cstr_tokenize(const char* instr, size_t len, int delim, cstr_cbfunc_t cbfunc, void* userp)
{
    size_t pos;
    size_t countlen;
    size_t iend;
    size_t elements;
    bool found;
    char* buf;
    char* data;
    char* nstr;
    countlen = 0;
    pos = 0;
    elements = 0;
    /*
    * check that the string actually contains $delim at all.
    * if that is not the case, then any further parsing would
    * be a waste of time.
    */
    found = cstr_find_char(instr, 0, len, delim, &pos);
    if(found == true)
    {
        /*
        * make a copy of $instr, and reference the buffer, so
        * we can use pointer arithmetics properly.
        */
        buf = cstr_copy(instr, len);
        data = buf;
        while(true)
        {
            /*
            * find the next delim.
            * if successful, pos is also the length of the tokendata.
            */
            iend = (len - countlen);
            found = cstr_find_char(data, 0, iend, delim, &pos);
            /*
            * if empty token pairs are encountered, i.e, ',foo,bar,,baz', then
            * skip string copying, since it would be a null-length string anyway.
            */
            if(found && (pos > 0))
            {
                elements++;
                /*
                * since we move data by pos+1, the string always starts at 0.
                */
                if((nstr = cstr_substr(data, iend, 0, pos)) != NULL)
                {
                    /*
                    * stop parsing altogether if cbfunc returns false.
                    */
                    if(cbfunc(nstr, pos, userp) == false)
                    {
                        break;
                    }
                }
            }

            /*
            * count up remaining string length
            */
            countlen += (pos + 1);

            /*
            * since remaining stringlength is always +1'd, it'll eventually
            * become len+1 (or, in a very unlikely case, more than that)
            */
            if((countlen == (len + 1)) || (countlen > len))
            {
                break;
            }

            /*
            * move pointer using dumb pointer arithmetic.
            * i usually try to avoid ptr arith, but in this case it's the
            * easiest (and likely least errorprone) way to move data.
            */
            data += pos + 1;
        }
        /*
        * free our previously allocated buffer
        */
        free(buf);
    }
    else
    {
        dbg("string doesn't contain any instance of '%c'", delim);
    }
    return elements;
}

