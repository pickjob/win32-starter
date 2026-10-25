// clang-format off
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "utils/log.h"
// clang-format on

#define IMPORT_DLL_NAME_MAX_LEN        260

#define IMPORT_DLL_IMPORT_NAME_MAX_LEN 4096

DWORD rva2Foa(DWORD dwRva, PIMAGE_SECTION_HEADER lpImageSectionHeaders, int nImageSectionSize);

char *readStringFromFile(HANDLE hFile, DWORD offset, size_t nMaxLen);