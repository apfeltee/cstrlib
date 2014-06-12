
#ifndef __cstr_functions_header
#define __cstr_functions_header

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#define CSTRLIB_VERSION 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

    
typedef bool(*cstr_cbfunc_t)
(
    /*
    * the allocated string.
    * needs to be free()'d after use-
    */
    char*,

    /*
    * size of the string.
    */
    size_t,

    /*
    * passed userdata, if any.
    */
    void*
);

typedef struct cdynstr_tag_t {
    char* buffer;
    size_t allocsize;
    size_t currentsize;
} cdynstr_t;

/**
* determine length of nullterminated string $str.
*/
size_t cstr_length(const char* str);

/**
 * a simple implementation of strndup, since
 * strndup is a GNU extension.
 */
char* cstr_copy(
    /*
    * input string.
    */
    const char* str,

    /*
    * length of input string.
    */
    size_t len
);

/**
* finds $findme in $inpstr.
*/
bool cstr_find_char(
    /*
    * the string to be scanned.
    */
    const char* inpstr,

    /*
    * at which index the search is intended to start.
    * example: if the whole string is to be searched, set it to 0.
    */
    size_t ibegin,

    /*
    * the furthest index to be used.
    * example: if the whole string is to be searched, $iend should
    * be the length of $inpstr.
    */
    size_t iend,

    /*
    * value to find-
    */
    int findme,

    /*
    * where the position will be stored.
    */
    size_t* res
);

/**
* similar to cstr_find_char, but searches for full string delimiters.
* if you wish to use to traverse a string, use it like cstr_find_char, but keep
* in mind that you plan ahead to iterate to the next position by using
* $findlen, instead of 1!
* the function 'cstr_tokenize_string' is a good example for this.
*
* arguments are, for most part, the same as for cstr_find_char, but
* with a few exceptions, of course.
*
* example:
*  size_t position;
*  bool found = cstr_find_string("foo===bar===baz", 0, 15, "===", 3, &position);
*/
bool cstr_find_string(
    const char* inpstr,
    size_t ibegin,
    size_t iend,

    /*
    * the string to search for.
    * must not be NULL.
    */
    const char* findme,

    /*
    * length of $findme.
    */
    size_t findlen,

    /*
    * where the position will be stored.
    * it is the position *before* $findme, so for example, in:
    *   "foo===bar===baz"
    * the first position would be 3.
    */
    size_t* res
);

/**
* copies a string from $pos_from to $pos_to.
* the returned string must be free()'d.
*/
char* cstr_substr(
    /*
    * the input string from which to read.
    */
    const char* inpstr,

    /*
    * length of $inpstr.
    */
    size_t inlen,

    /*
    * position at which the substring starts.
    */
    size_t pos_from,

    /*
    * position at which the substring ends.
    */
    size_t pos_to
);

/**
* tokenizes (splits) a string at a given delimiter.
*/
size_t cstr_tokenize(
    /*
    * the string to be tokenized.
    * if empty tokens are encountered (i.e., "foo,bar,,baz,"), then
    * those pairs are discarted, since they would be zero-length strings.
    * must not be NULL.
    */
    const char* instr,

    /*
    * the length of $instr.
    */
    size_t len,

    /*
    * the token value used for splitting.
    */
    int delim,

    /*
    * the callback function.
    * see the documentation for cstr_cbfunc_t for more information.
    */
    cstr_cbfunc_t cbfunc,

    /*
    * userdata which is passed to $cbfunc.
    */
    void* userp
);

/**
* tokenizes (splits) a string at a given full string delimiter.
*/
size_t cstr_tokenize_string(
    /*
    * the string to be tokenized.
    * if empty tokens are encountered (i.e., "fooDELIMbarDELIMDELIMbazDELIM"), then
    * those pairs are discarted, since they would be zero-length strings.
    * must not be NULL.
    */
    const char* instr,

    /*
    * the length of $instr.
    */
    size_t len,

    /*
    * the token string used for splitting.
    */
    const char* delim,

    /*
    * the length of $delim.
    */
    size_t dellen,

    /*
    * the callbackfunction.
    * see the documentation for cstr_cbfunc_t for more information.
    */
    cstr_cbfunc_t cbfunc,

    /*
    * userdata which is passed to $cbfunc.
    */
    void* userp
);

/**
* turn writable string $inbuf uppercase.
*/
char* cstr_toupper(
    char* inbuf,
    size_t len
);

/**
* turn writable string $inbuf lowercase.
*/
char* cstr_tolower(
    char* inbuf,
    size_t len
);



/**
* perform a primitive wildcard comparison.
*
* supported pattern tokens:
*   '*':
*       match everything until end of string OR until first match of
*      follow up pattern.
*
*   '^':
*      currently only useful when pattern starts with '^'.
*
*   '?':
*       matches any arbitrary single character.
*/
bool cstr_wildcmpn(
    const char* wild,
    size_t wlen,
    const char* str,
    size_t slen,
    bool icase
);

/**
* same as cstr_wildcmpn, but the length for $wild and $str
* are determined through cstr_length().
*/
bool cstr_wildcmp(
    const char* wild,
    const char* str,
    bool icase
);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __cstr_functions_header */
