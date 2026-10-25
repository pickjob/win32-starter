#include "utils/common.h"

// clang-format off
#include <stdlib.h>

#include <windows.h>
// clang-format on

wchar_t *utf8_to_utf16(const char *utf8_str) {
    if (!utf8_str) {
        return NULL;
    }
    int len = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8_str, -1, NULL, 0);
    if (len == 0) {
        return NULL;
    }
    wchar_t *utf16_str = malloc((size_t)len * sizeof(wchar_t));
    if (!utf16_str) {
        return NULL;
    }
    if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, utf8_str, -1, utf16_str, len) == 0) {
        free(utf16_str);
        return NULL;
    }
    return utf16_str;
}

char *utf16_to_utf8(const wchar_t *utf16_str) {
    if (!utf16_str) {
        return NULL;
    }
    int len = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16_str, -1, NULL, 0, NULL, NULL);
    if (len == 0) {
        return NULL;
    }
    char *utf8_str = malloc((size_t)len);
    if (!utf8_str) {
        return NULL;
    }
    if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, utf16_str, -1, utf8_str, len, NULL, NULL) == 0) {
        free(utf8_str);
        return NULL;
    }
    return utf8_str;
}