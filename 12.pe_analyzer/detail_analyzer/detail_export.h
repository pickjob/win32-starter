// clang-format off
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "utils/log.h"
#include "detail_common.h"
// clang-format on

typedef struct _EXPORT_FUNCTION {
    DWORD Ordinal;
    DWORD Rva;
    DWORD Foa;
    char  szFunctionName[IMPORT_DLL_NAME_MAX_LEN];
} EXPORT_FUNCTION;
typedef EXPORT_FUNCTION *PEXPORT_FUNCTION;

void                     analyze_export(HANDLE hFile, DWORD dwExportRva, DWORD dwExportSize, PIMAGE_SECTION_HEADER lpImageSectionHeaders, int nImageSectionSize);