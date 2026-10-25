#include "detail_import.h"

//
// 导入目录分析
//      IMAGE_DIRECTORY_ENTRY_IMPORT: RVA, 指向IMAGE_IMPORT_DESCRIPTOR(IDT(Import Directory Table))结构的数组, 多一条全零记录
//      IMAGE_IMPORT_DESCRIPTOR
//          OriginalFirstThunk: RVA, 指向IMAGE_THUNK_DATA(INT(Import Name Table), ILT(Import Lookup Table))结构的数组, 多一条全零记录
//          Name: RVA, 指向导入DLL名称的ASCII字符串
//          FirstThunk: RVA, 指向IMAGE_THUNK_DATA(IAT(Import Address Table)), 加载后会变成导入函数绝对地址
//          TimeDateStamp: 时间戳
//          ForwarderChain
//      IMAGE_THUNK_DATA32 / IMAGE_THUNK_DATA64:
//          ForwarderString: 最高位为1, 指向导入函数的序号
//          AddressOfData: 最高位为0, RVA, 指向IMAGE_IMPORT_BY_NAME结构, 提供导入函数Hint, 名称
//      IMAGE_IMPORT_BY_NAME:
//          Hint: 函数序号
//          Name[1]: RVA, 指向导入函数名称的ASCII字符串
//
void analyze_import(int nPeType, HANDLE hFile, DWORD dwImportRva, DWORD dwImportSize, PIMAGE_SECTION_HEADER lpImageSectionHeaders, int nImageSectionSize) {
    (void)dwImportSize;
    DWORD         dwFileReadByte           = 0;
    LARGE_INTEGER nFileReadOffset          = {0};
    DWORD         nImageImportDescritorFoa = rva2Foa(dwImportRva, lpImageSectionHeaders, nImageSectionSize);
    nFileReadOffset.QuadPart               = nImageImportDescritorFoa;
    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
    IMAGE_IMPORT_DESCRIPTOR stImageImportDescriptor = {0};
    if (FALSE == ReadFile(hFile, &stImageImportDescriptor, sizeof(stImageImportDescriptor), &dwFileReadByte, NULL)) {
        LOG_LAST_ERROR("ReadFile: IMAGE_IMPORT_DESCRIPTOR");
        return;
    }
    LOG_INFO("IMPORT_DIRECTORY: RVA: 0x%X, FOA: 0x%X", dwImportRva, nImageImportDescritorFoa);
    while (stImageImportDescriptor.Name) {
        DWORD dwDllNameFoa = rva2Foa(stImageImportDescriptor.Name, lpImageSectionHeaders, nImageSectionSize);
        char *szDllName    = readStringFromFile(hFile, dwDllNameFoa, IMPORT_DLL_NAME_MAX_LEN);
        if (NULL != szDllName) {
            LOG_INFO(
                "IMAGE_IMPORT_DESCRIPTOR Name: %s, OriginalFirstThunk: 0x%X, FirstThunk: 0x%X, RVA: 0x%X, FOA: 0x%X",
                szDllName,
                stImageImportDescriptor.OriginalFirstThunk,
                stImageImportDescriptor.FirstThunk,
                dwDllNameFoa
            );
        }
        free(szDllName);
        // OriginalFirstThunk(ILT) 为 0 时(绑定导入)退化为 FirstThunk(IAT)
        DWORD dwImageThunkRva     = stImageImportDescriptor.OriginalFirstThunk ? stImageImportDescriptor.OriginalFirstThunk : stImageImportDescriptor.FirstThunk;
        DWORD dwImageThunkDataFoa = rva2Foa(dwImageThunkRva, lpImageSectionHeaders, nImageSectionSize);
        if (0 == nPeType) {
            while (TRUE) {
                nFileReadOffset.QuadPart = dwImageThunkDataFoa;
                SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
                IMAGE_THUNK_DATA32 stImageThunkData32 = {0};
                if (FALSE == ReadFile(hFile, &stImageThunkData32, sizeof(stImageThunkData32), &dwFileReadByte, NULL)) {
                    LOG_LAST_ERROR("ReadFile: IMAGE_THUNK_DATA32");
                    break;
                }
                if (0 == stImageThunkData32.u1.AddressOfData) { // ILT/IAT 以 0 结尾
                    break;
                }
                if (IMAGE_ORDINAL_FLAG32 & stImageThunkData32.u1.AddressOfData) {
                    LOG_INFO(
                        "IMAGE_THUNK_DATA32: 0x%X(Ordinal: 0x%X), FOA: 0x%X",
                        stImageThunkData32.u1.AddressOfData,
                        IMAGE_ORDINAL32(stImageThunkData32.u1.AddressOfData),
                        dwImageThunkDataFoa
                    );
                } else {
                    DWORD dwImageImportByNameFoa = rva2Foa((DWORD)stImageThunkData32.u1.AddressOfData, lpImageSectionHeaders, nImageSectionSize);
                    WORD  wImageImportHint       = 0;
                    nFileReadOffset.QuadPart     = dwImageImportByNameFoa;
                    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
                    if (FALSE == ReadFile(hFile, &wImageImportHint, sizeof(wImageImportHint), &dwFileReadByte, NULL)) {
                        LOG_LAST_ERROR("ReadFile: IMAGE_IMPORT_BY_NAME.Hint");
                        break;
                    }
                    char *szDllFunctionName = readStringFromFile(hFile, dwImageImportByNameFoa + sizeof(wImageImportHint), IMPORT_DLL_IMPORT_NAME_MAX_LEN);
                    if (NULL != szDllFunctionName) {
                        LOG_INFO(
                            "IMAGE_THUNK_DATA32: IMAGE_IMPORT_BY_NAME Hint: 0x%X, Name: %s, RVA: 0x%X, FOA: 0x%X",
                            wImageImportHint,
                            szDllFunctionName,
                            stImageThunkData32.u1.AddressOfData,
                            dwImageImportByNameFoa
                        );
                    }
                    free(szDllFunctionName);
                }
                dwImageThunkDataFoa = dwImageThunkDataFoa + sizeof(IMAGE_THUNK_DATA32);
            }
        } else if (1 == nPeType) {
            while (TRUE) {
                nFileReadOffset.QuadPart = dwImageThunkDataFoa;
                SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
                IMAGE_THUNK_DATA64 stImageThunkData64 = {0};
                if (FALSE == ReadFile(hFile, &stImageThunkData64, sizeof(stImageThunkData64), &dwFileReadByte, NULL)) {
                    LOG_LAST_ERROR("ReadFile: IMAGE_THUNK_DATA64");
                    break;
                }
                if (0 == stImageThunkData64.u1.AddressOfData) { // ILT/IAT 以 0 结尾
                    break;
                }
                if (IMAGE_ORDINAL_FLAG64 & stImageThunkData64.u1.AddressOfData) {
                    LOG_INFO(
                        "IMAGE_THUNK_DATA64: 0x%llX(Ordinal: 0x%llX), FOA: 0x%X",
                        stImageThunkData64.u1.AddressOfData,
                        IMAGE_ORDINAL64(stImageThunkData64.u1.AddressOfData),
                        dwImageThunkDataFoa
                    );
                } else {
                    DWORD dwImageImportByNameFoa = rva2Foa((DWORD)stImageThunkData64.u1.AddressOfData, lpImageSectionHeaders, nImageSectionSize);
                    WORD  wImageImportHint       = 0;
                    nFileReadOffset.QuadPart     = dwImageImportByNameFoa;
                    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
                    if (FALSE == ReadFile(hFile, &wImageImportHint, sizeof(wImageImportHint), &dwFileReadByte, NULL)) {
                        LOG_LAST_ERROR("ReadFile: IMAGE_IMPORT_BY_NAME.Hint");
                        break;
                    }
                    char *szDllFunctionName = readStringFromFile(hFile, dwImageImportByNameFoa + sizeof(wImageImportHint), IMPORT_DLL_IMPORT_NAME_MAX_LEN);
                    if (NULL != szDllFunctionName) {
                        LOG_INFO(
                            "IMAGE_THUNK_DATA64: IMAGE_IMPORT_BY_NAME Hint: 0x%X, Name: %s, RVA: 0x%llX, FOA: 0x%X",
                            wImageImportHint,
                            szDllFunctionName,
                            stImageThunkData64.u1.AddressOfData,
                            dwImageImportByNameFoa
                        );
                    }
                    free(szDllFunctionName);
                }
                dwImageThunkDataFoa = dwImageThunkDataFoa + sizeof(IMAGE_THUNK_DATA64);
            }
        }

        nImageImportDescritorFoa = nImageImportDescritorFoa + sizeof(stImageImportDescriptor);
        nFileReadOffset.QuadPart = nImageImportDescritorFoa;
        SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
        if (FALSE == ReadFile(hFile, &stImageImportDescriptor, sizeof(stImageImportDescriptor), &dwFileReadByte, NULL)) {
            LOG_LAST_ERROR("ReadFile: IMAGE_IMPORT_DESCRIPTOR");
            return;
        }
    }
}