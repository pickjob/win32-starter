// clang-format off
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "utils/log.h"
#include "detail_common.h"
// clang-format on

void analyze_import(int nPeType, HANDLE hFile, DWORD dwImportRva, DWORD dwImportSize, PIMAGE_SECTION_HEADER lpImageSectionHeaders, int nImageSectionSize);