
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstrlib.h>

bool doprint(char* str, size_t len, void* userp)
{
    size_t sl;
    (void)userp;
    sl = strlen(str);
    printf("str(%d, sl=%d) = \"%s\"\n", len, sl, str);
    free(str);
    return true;
}


int main(int argc, char* argv[], char* envp[])
{
    size_t len;
    size_t el;
    size_t dlen;
    size_t pos;
    {
        const char str[] =
        "port=8080\n"
        "docroot=/srv/www\n"
        "indexfiles=index.html,default.html\n"
        "usecgi=true\n"
        ;
        len = (sizeof(str) - 1);
        el = cstr_tokenize(str, len, '\n', doprint, NULL);
        printf("tokenize: extracted %d elements\n", el);
    }
    {
        const char str[] =
        "red<>green<>blue<>black<>white"
        ;
        const char del[] = "<>";
        len = (sizeof(str) - 1);
        dlen = (sizeof(del) - 1);
        el = cstr_tokenize_string(str, len, del, dlen, doprint, NULL);
        printf("cstr_tokenize_string: extracted %d elements\n", el);
    }
    {
        const char str[] = "foo===bar===baz";
        const char del[] = "===";
        len = (sizeof(str) - 1);
        dlen = (sizeof(del) - 1);
        cstr_find_string(str, 0, len, del, dlen, &pos);
        printf("position = %d\n", pos);
    }
    return 0;
}
