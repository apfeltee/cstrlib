cstrlib
=======

cstrlib is a library for scanning/parsing/manipulating C char arrays, commonly known as "c strings".
Further, it focuses on simple algorithms, readable, well-documented (room for improvement) code, with clear
structures, and little nonsense.

Because of this, some functions may appear verbose, but for good reason: To offer excellent control over
the functionality over each function.

In some places, however, cstrlib 'merely' implements algorithms commonly provided as GNU extensions through GCC, and the GNU
C standard library. A good example of such a function is `cstr_copy` - an implementation of `strndup`.

As with all software within this github organization, it's completely, totally, entirely, utterly public domain.
No license nonsense, do-what-you-want-with-it, no copyleft, no copyright, no restrictions.
Download it, sell it, wipe your arse with it, it doesn't matter.
The only thing that matters (at least to me), is to provide useful algorithms without any strings attached.
