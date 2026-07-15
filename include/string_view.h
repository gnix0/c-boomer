#ifndef STRING_VIEW_H
#define STRING_VIEW_H

#include <stddef.h>
#include <stdbool.h>

typedef struct {
    const char *data;
    size_t len;

} String_View;

String_View sv(const char *cstr);
void sv_trim(String_View *sv);
String_View sv_chop_by_delim(String_View *sv, char delim);
bool sv_eq_cstr(String_View sv, const char *cstr);
bool sv_to_double(String_View sv, double *result);
int sv_contains(String_View sv, char character);

#endif
