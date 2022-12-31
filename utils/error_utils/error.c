#include "utils/error.h"

// 展示最后操作错误
BOOL ShowLastError(LPTSTR lpDetail, LPTSTR lpTag) {
    DWORD nErrorCode = GetLastError();
    if (EXIT_SUCCESS == nErrorCode) {
        return FALSE;
    }
    LPTSTR lpErrorText = NULL;
    BOOL   fOk
        = FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS,
                        NULL,
                        nErrorCode,
                        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                        (LPTSTR) &lpErrorText,
                        0,
                        NULL);
    if (!fOk) {
        HMODULE hLibrary = LoadLibraryEx(_T("netmsg.dll"), NULL, DONT_RESOLVE_DLL_REFERENCES);
        if (NULL != hLibrary) {
            fOk = FormatMessage(FORMAT_MESSAGE_FROM_HMODULE | FORMAT_MESSAGE_IGNORE_INSERTS
                                    | FORMAT_MESSAGE_ALLOCATE_BUFFER,
                                hLibrary,
                                nErrorCode,
                                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                                lpErrorText,
                                0,
                                NULL);
            if (!fOk) {
                lpErrorText = NULL;
            }
            FreeLibrary(hLibrary);
        }
    }
    if (!fOk) {
        lpErrorText = _T("未知错误!");
    }
    LPTSTR  lpFromatErrorInfo = _T("格式化错误信息!");
    size_t   nTotalLength     = 0;
    size_t   nLength          = 0;
    HRESULT hResult           = StringCchLength(lpDetail, STRSAFE_MAX_CCH, &nLength);
    if (FAILED(hResult)) {
        MessageBox(NULL, lpFromatErrorInfo, lpTag, MB_OK);
        return FALSE;
    }
    nTotalLength += nLength;
    hResult = StringCchLength(lpTag, STRSAFE_MAX_CCH, &nLength);
    if (FAILED(hResult)) {
        MessageBox(NULL, lpFromatErrorInfo, lpTag, MB_OK);
        return FALSE;
    }
    nTotalLength += nLength;
    hResult = StringCchLength(lpErrorText, STRSAFE_MAX_CCH, &nLength);
    if (FAILED(hResult)) {
        MessageBox(NULL, lpFromatErrorInfo, lpTag, MB_OK);
        return FALSE;
    }
    nTotalLength += nLength;
    TCHAR szErrorInfo[nTotalLength + 100];
    hResult = StringCchPrintf(szErrorInfo, _countof(szErrorInfo), _T("%s(%d-%s)"), lpErrorText, nErrorCode, lpDetail);
    if (!fOk) {
        LocalFree(lpErrorText);
    }
    if (FAILED(hResult)) {
        MessageBox(NULL, lpFromatErrorInfo, lpTag, MB_OK);
        return FALSE;
    }
    MessageBox(NULL, szErrorInfo, lpTag, MB_OK);

    return TRUE;
}
