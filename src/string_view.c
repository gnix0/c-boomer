#include "string_view.h"
#include <ctype.h>
#include <string.h>

String_View sv(const char *cstr)
{
    return (String_View){
        .data = cstr,
        .len = strlen(cstr),
    };
}

void sv_chop_left(String_View *sv, size_t n)
{
    if (n > sv->len)
        n = sv->len;

    sv->len -= n;
    sv->data += n;
}

void sv_chop_right(String_View *sv, size_t n)
{
    if (n > sv->len)
        n = sv->len;

    if (sv->len == 0)
        return;

    sv->len -= n;
}

void sv_trim_left(String_View *sv)
{
    while (sv->len > 0 && isspace(sv->data[0])) {
        sv_chop_left(sv, 1);
    }
}

void sv_trim_right(String_View *sv)
{
    while (sv->len > 0 && isspace(sv->data[sv->len - 1])) {
        sv_chop_right(sv, 1);
    }
}

void sv_trim(String_View *sv)
{
    sv_trim_left(sv);
    sv_trim_right(sv);
}
