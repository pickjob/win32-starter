#include "detail_export.h"

//
// 导出目录分析
//      IMAGE_EXPORT_DIRECTORY
//          Name: RVA, 模块名称ASCII字符串
//          NumberOfNames: 导出函数数量(按名称)
//          AddressOfNames: RVA, ENT(Export Name Table), 指向导出函数名称字符串RVA的数组
//
//          Base: 导出函数起始序号
//          NumberOfFunctions: 导出函数总数
//          AddressOfFunctions: RVA, EAT(Export Address Table), 指向导出函数地址表RVA数组, 索引 = 序号 - Base
//
//          AddressOfNameOrdinals: RVA, EOT(Export Ordinal Table), 指向和ENT(Export Name Table)顺序一致的的次序, 用于名称 → 序号 → 地址的映射
//
void analyze_export(HANDLE hFile, DWORD dwExportRva, DWORD dwExportSize, PIMAGE_SECTION_HEADER lpImageSectionHeaders, int nImageSectionSize) {
    (void)dwExportSize;
    DWORD         dwFileReadByte  = 0;
    LARGE_INTEGER nFileReadOffset = {0};
    DWORD         dwExportFoa     = rva2Foa(dwExportRva, lpImageSectionHeaders, nImageSectionSize);
    nFileReadOffset.QuadPart = dwExportFoa;
    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
    IMAGE_EXPORT_DIRECTORY stImageExportDirectory = {0};
    if (FALSE == ReadFile(hFile, &stImageExportDirectory, sizeof(stImageExportDirectory), &dwFileReadByte, NULL)) {
        LOG_LAST_ERROR("ReadFile: IMAGE_EXPORT_DIRECTORY");
        return;
    }
    DWORD dwBase                 = stImageExportDirectory.Base;
    DWORD dwExportNameNumber     = stImageExportDirectory.NumberOfNames;
    DWORD dwExportFunctionNumber = stImageExportDirectory.NumberOfFunctions;
    DWORD dwDllNameFoa           = rva2Foa(stImageExportDirectory.Name, lpImageSectionHeaders, nImageSectionSize);
    char *szDllName              = readStringFromFile(hFile, dwDllNameFoa, IMPORT_DLL_NAME_MAX_LEN);
    LOG_INFO(
        "EXPORT_DIRECTORY: DllName: %s, FOA: 0x%X, Base: 0x%X, NumberOfNames: 0x%X, NumberOfFunctions: 0x%X",
        NULL != szDllName ? szDllName : "(null)",
        dwDllNameFoa,
        dwBase,
        dwExportNameNumber,
        dwExportFunctionNumber
    );
    free(szDllName);

    if (0 == dwExportFunctionNumber) {
        return;
    }
    PEXPORT_FUNCTION lpExportFunctions = calloc(dwExportFunctionNumber, sizeof(EXPORT_FUNCTION)); // 仅按序号导出的函数没有名称, 需零初始化
    if (NULL == lpExportFunctions) {
        LOG_ERROR("calloc: EXPORT_FUNCTION");
        return;
    }
    //
    // EAT(Export Address Table): 导出函数地址表, 表项为 DWORD(RVA), 索引 = 序号 - Base
    //
    DWORD dwEatFoa = rva2Foa(stImageExportDirectory.AddressOfFunctions, lpImageSectionHeaders, nImageSectionSize);
    for (DWORD i = 0; i < dwExportFunctionNumber; i++) {
        DWORD dwFunctionRva      = 0;
        nFileReadOffset.QuadPart = dwEatFoa;
        SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
        if (FALSE == ReadFile(hFile, &dwFunctionRva, sizeof(dwFunctionRva), &dwFileReadByte, NULL)) {
            LOG_LAST_ERROR("ReadFile: IMAGE_EXPORT_DIRECTORY.AddressOfFunctions");
            free(lpExportFunctions);
            return;
        }
        PEXPORT_FUNCTION lpExportFunction = lpExportFunctions + i;
        lpExportFunction->Ordinal         = dwBase + i;
        lpExportFunction->Rva             = dwFunctionRva;
        lpExportFunction->Foa             = rva2Foa(dwFunctionRva, lpImageSectionHeaders, nImageSectionSize);
        dwEatFoa                          = dwEatFoa + sizeof(dwFunctionRva);
    }
    //
    // ENT(Export Name Table): 导出函数名称字符串 RVA 数组, 表项为 DWORD
    // EOT(Export Ordinal Table): 与 ENT 顺序一一对应, 表项为 WORD, 存放 EAT 索引(即 序号 - Base)
    //
    DWORD dwEntFoa = rva2Foa(stImageExportDirectory.AddressOfNames, lpImageSectionHeaders, nImageSectionSize);
    DWORD dwEotFoa = rva2Foa(stImageExportDirectory.AddressOfNameOrdinals, lpImageSectionHeaders, nImageSectionSize);
    for (DWORD i = 0; i < dwExportNameNumber; i++) {
        WORD dwEatIndex          = 0;
        nFileReadOffset.QuadPart = dwEotFoa;
        SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
        if (FALSE == ReadFile(hFile, &dwEatIndex, sizeof(dwEatIndex), &dwFileReadByte, NULL)) {
            LOG_LAST_ERROR("ReadFile: IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals");
            free(lpExportFunctions);
            return;
        }
        DWORD dwNameRva          = 0;
        nFileReadOffset.QuadPart = dwEntFoa;
        SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
        if (FALSE == ReadFile(hFile, &dwNameRva, sizeof(dwNameRva), &dwFileReadByte, NULL)) {
            LOG_LAST_ERROR("ReadFile: IMAGE_EXPORT_DIRECTORY.AddressOfNames");
            free(lpExportFunctions);
            return;
        }
        if (dwEatIndex >= dwExportFunctionNumber) { // 恶意/损坏文件: 索引越界会写坏堆内存
            LOG_WARN("IMAGE_EXPORT_DIRECTORY.AddressOfNameOrdinals[0x%X]: EAT 索引 0x%X 越界, 跳过", i, dwEatIndex);
        } else {
            DWORD   dwNameFoa = rva2Foa(dwNameRva, lpImageSectionHeaders, nImageSectionSize);
            char   *szName    = readStringFromFile(hFile, dwNameFoa, IMPORT_DLL_NAME_MAX_LEN);
            HRESULT hr        = StringCchCopyA(lpExportFunctions[dwEatIndex].szFunctionName, _countof(lpExportFunctions[dwEatIndex].szFunctionName), NULL != szName ? szName : "");
            if (FAILED(hr)) {
                LOG_ERROR("StringCchCopyA: EXPORT_FUNCTION.szFunctionName");
            }
            free(szName);
        }
        dwEntFoa = dwEntFoa + sizeof(dwNameRva);
        dwEotFoa = dwEotFoa + sizeof(dwEatIndex);
    }
    for (DWORD i = 0; i < dwExportFunctionNumber; i++) {
        PEXPORT_FUNCTION lpExportFunction = lpExportFunctions + i;
        LOG_INFO(
            "EXPORT_FUNCTION: Ordinal: 0x%X, RVA: 0x%X, FOA: 0x%X, Name: %s",
            lpExportFunction->Ordinal,
            lpExportFunction->Rva,
            lpExportFunction->Foa,
            '\0' != lpExportFunction->szFunctionName[0] ? lpExportFunction->szFunctionName : "(仅按序号导出)"
        );
    }
    free(lpExportFunctions);
}