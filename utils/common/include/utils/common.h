#ifndef COMMON_H
#define COMMON_H

// clang-format off
#include <wchar.h>
// clang-format on

#ifdef __cplusplus
extern "C" {
#endif

wchar_t *utf8_to_utf16(const char *utf8_str);
char    *utf16_to_utf8(const wchar_t *utf16_str);

#ifdef __cplusplus
}
#endif

#endif /* COMMON_H */