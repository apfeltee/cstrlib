
#include "private.h"

enum
{
    kBeginOfData = '^',
    kAnyString   = '*',
    kAnyChar     = '?',
};

static int wildlower(int c, bool icase)
{
    if(icase)
    {
        return tolower(c);
    }
    return c;
}

bool cstr_wildcmpn(const char* wild, size_t wlen, const char* str, size_t slen, bool icase)
{
    size_t wi;
    size_t si;
    size_t origwi;
    size_t origsi;
    int cw;
    int cs;
    wi = si = 0;
    origwi = origsi = 0;
    if((wlen == 0) || (slen == 0))
    {
        dbg("wlen is 0 and slen is 0, nothing to do\n");
        return false;
    }
    if((wild == NULL) || (str == NULL))
    {
        dbg("wild is NULL and str is NULL, nothing to do\n");
        return false;
    }
    if(wild[wi] == kBeginOfData)
    {
        if(wild[wi+1] != str[si])
        {
            return false;
        }
        wi++;
    }
    while((si != slen) && (wild[wi] != kAnyString))
    {
        cw = wildlower(wild[wi], icase);
        cs = wildlower(str[si], icase);
        if((cw != cs) && (cw != kAnyChar))
        {
            return false;
        }
        wi++;
        si++;
    }
    while(si != slen)
    {
        if(wild[wi] == kAnyString)
        {
            if((++wi) == wlen)
            {
                return true;
            }
            origwi = wi;
            origsi = si + 1;
        }
        else if((wildlower(wild[wi], icase) == wildlower(str[si], icase)) || (wild[wi] == kAnyChar))
        {
            wi++;
            si++;
        }
        else
        {
            wi = origwi;
            si = origsi++;
        }
    }
    while(wild[wi] == kAnyString)
    {
        wi++;
    }
    return (wi == wlen);
}

bool cstr_wildcmp(const char* wild, const char* str, bool icase)
{
    return cstr_wildcmpn(
        wild, cstr_length(wild),
        str, cstr_length(str),
        icase
    );
}

