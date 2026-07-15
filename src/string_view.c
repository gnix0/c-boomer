#include "string_view.h"
#include <ctype.h>
#include <errno.h>
#include <stdbool.h>
#include <stdlib.h>
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

    sv->len -= n;
}

void sv_trim_left(String_View *sv)
{
    while (sv->len > 0 && isspace((unsigned char)sv->data[0])) {
        sv_chop_left(sv, 1);
    }
}

void sv_trim_right(String_View *sv)
{
    while (sv->len > 0 && isspace((unsigned char)sv->data[sv->len - 1])) {
        sv_chop_right(sv, 1);
    }
}

void sv_trim(String_View *sv)
{
    sv_trim_left(sv);
    sv_trim_right(sv);
}

String_View sv_chop_by_delim(String_View *sv, char delim)
{
    size_t i = 0;
    while (i < sv->len && sv->data[i] != delim) {
        i += 1;
    }

    String_View result = {
        .data = sv->data,
        .len = i,
    };

    if (i < sv->len)
        sv_chop_left(sv, i + 1);
    else
        sv_chop_left(sv, i);

    return result;
}

bool sv_eq_cstr(String_View sv, const char *cstr)
{
    size_t len = strlen(cstr);
    return sv.len == len && memcmp(sv.data, cstr, len) == 0;
}

bool sv_to_double(String_View sv, double *result)
{
    char buffer[128];
    if (sv.len >= sizeof buffer)
        return false;

    memcpy(buffer, sv.data, sv.len);
    buffer[sv.len] = '\0';

    errno = 0;

    char *end;
    double value = strtod(buffer, &end);

    if (end == buffer || *end != '\0' || errno == ERANGE)
        return false;

    *result = value;
    return true;
}

int sv_contains(String_View sv, char character)
{
    size_t i = 0;
    while (i < sv.len) {
        if (sv.data[i] == character)
            return 1;

        i += 1;
    }

    return 0;
}
