/**
 * UNICODE、MBS转换:
 *      MultiByteToWideChar(
 *          [in]            UINT                              CodePage,
 *          [in]            DWORD                             dwFlags,
 *          [in]            _In_NLS_string_(cbMultiByte)LPCCH lpMultiByteStr,
 *          [in]            int                               cbMultiByte,
 *          [out, optional] LPWSTR                            lpWideCharStr,
 *          [in]            int                               cchWideChar
 *      ): int
 *          dwFlags:
 *              MB_PRECOMPOSED
 *              MB_COMPOSITE
 *              MB_ERR_INVALID_CHARS
 *              MB_USEGLYPHCHARS
 *          cbMultiByte: 0 函数返回lpWideCharStr需要大小
 *          CodePage:
 *              CP_ACP: ANSI
 *              CP_UTF8: UTF-8
 *      WideCharToMultiByte(
 *          [in]            UINT                               CodePage,
 *          [in]            DWORD                              dwFlags,
 *          [in]            _In_NLS_string_(cchWideChar)LPCWCH lpWideCharStr,
 *          [in]            int                                cchWideChar,
 *          [out, optional] LPSTR                              lpMultiByteStr,
 *          [in]            int                                cbMultiByte,
 *          [in, optional]  LPCCH                              lpDefaultChar,
 *          [out, optional] LPBOOL                             lpUsedDefaultChar
 *      ): int
 *          dwFlags:
 *              WC_COMPOSITECHECK | WC_DEFAULTCHAR: 异常替换成默认字符
 *              WC_ERR_INVALID_CHARS: 异常返回0
 *              WC_NO_BEST_FIT_CHARS
 *          cbMultiByte: 0 函数返回lpMultiByteStr需要大小, 包括NULL
 * strsafe.h: 字符串操纵函数(按字节、字符)
 *      StringCchLength(
 *          [in]  LPTSTR          psz,
 *          [in]  size_t          cchMax,   // STRSAFE_MAX_CCH
 *          [out] size_t          *pcchLength
 *      ): HRESULT 字符串长度
 *      StringCchPrintf(
 *          [out] LPTSTR          pszDest,
 *          [in]  size_t          cchDest,
 *          [in]  STRSAFE_LPCWSTR pszFormat,
 *          ...             
 *      ): HRESULT 字符串格式化
 **/
