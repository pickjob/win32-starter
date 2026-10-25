#include "detail_common.h"

DWORD rva2Foa(DWORD dwRva, PIMAGE_SECTION_HEADER lpImageSectionHeaders, int nImageSectionSize) {
    DWORD dwFoa = 0;
    for (int i = 0; i < nImageSectionSize; i++) {
        PIMAGE_SECTION_HEADER lpImageSectionHeader = lpImageSectionHeaders + i;
        if (dwRva >= lpImageSectionHeader->VirtualAddress && dwRva < (lpImageSectionHeader->VirtualAddress + lpImageSectionHeader->Misc.VirtualSize)) {
            dwFoa = lpImageSectionHeader->PointerToRawData + (dwRva - lpImageSectionHeader->VirtualAddress);
        }
    }
    return dwFoa;
}

char *readStringFromFile(HANDLE hFile, DWORD offset, size_t nMaxLen) {
    if (nMaxLen < 1) {
        return NULL;
    }
    LARGE_INTEGER nFileReadOffset = {0};
    nFileReadOffset.QuadPart      = offset;
    if (FALSE == SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN)) {
        LOG_LAST_ERROR("SetFilePointerEx: readStringFromFile");
        return NULL;
    }
    char *szBuffer = malloc(nMaxLen);
    if (NULL == szBuffer) {
        LOG_ERROR("malloc: readStringFromFile");
        return NULL;
    }
    size_t len = 0;

    while (len < nMaxLen - 1) {
        char  chunk[256];
        DWORD dwFileReadByte = 0;
        if (FALSE == ReadFile(hFile, chunk, sizeof(chunk), &dwFileReadByte, NULL)) {
            LOG_LAST_ERROR("ReadFile: readStringFromFile");
            free(szBuffer);
            return NULL;
        }
        if (0 == dwFileReadByte) { // 到达文件末尾
            LOG_WARN("readStringFromFile: FOA-0x%X 处字符串未以'\\0'结尾", offset);
            break;
        }
        for (DWORD i = 0; i < dwFileReadByte; i++) {
            if ('\0' == chunk[i]) { // 遇到结束符, 无需再读取
                szBuffer[len] = '\0';
                return szBuffer;
            }
            if (len == nMaxLen - 1) { // 缓冲区已满
                break;
            }
            szBuffer[len++] = chunk[i];
        }
    }
    if (len == nMaxLen - 1) { // 字符串长度超过缓冲区容量
        LOG_WARN("readStringFromFile: FOA-0x%X 处字符串超过 %zu 字节, 已截断", offset, nMaxLen - 1);
    }
    szBuffer[len] = '\0';
    return szBuffer;
}