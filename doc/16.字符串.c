/**
 * 函数
 *      UNICODE、MBS转换
 *          MultiByteToWideChar
 *              dwFlags:
 *                  MB_PRECOMPOSED
 *                  MB_COMPOSITE
 *                  MB_ERR_INVALID_CHARS
 *                  MB_USEGLYPHCHARS
 *              cbMultiByte: 0 函数返回lpWideCharStr需要大小
 *              CodePage:
 *                  CP_ACP: ANSI
 *                  CP_UTF8: UTF-8
 *          WideCharToMultiByte
 *              dwFlags:
 *                  WC_COMPOSITECHECK | WC_DEFAULTCHAR: 异常替换成默认字符
 *                  WC_ERR_INVALID_CHARS: 异常返回0
 *                  WC_NO_BEST_FIT_CHARS
 *              cbMultiByte: 0 函数返回lpMultiByteStr需要大小, 包括NULL
 *      windows函数
 *          	lstrcat: 将一个字符串追加到另一个字符串
 *              lstrcmp: 比较两个字符字符串
 *              lstrcmpi: 比较两个字符字符串
 *              lstrcpy: 将字符串复制到缓冲区
 *              lstrcpyn: 将源字符串中的指定数量的字符复制到缓冲区中
 *              lstrlen: 确定指定字符串的长度(不包括终止 null 字符)
 *      strsafe.h
 *          字符
 *              StringCchCat / StringCchCatEx: 将一个字符串连接到另一个字符串
 *              StringCchCatN / StringCchCatNEx: 将指定数量的字符从一个字符串连接到另一个字符串
 *              StringCchCopy / StringCchCopyEx: 将一个字符串复制到另一个字符串
 *              StringCchCopyN / StringCchCopyNEx: 将指定的字符数从一个字符串复制到另一个字符串
 *              StringCchGets / StringCchGetsEx: 从 stdin 获取一行文本，最多包括换行符 （'\n'）
 *              StringCchPrintf / StringCchPrintfEx: 将数据写入指定的字符串
 *              StringCchVPrintf / StringCchVPrintfEx: 使用指向参数列表的指针将数据写入指定字符串
 *              StringCchLength: 确定字符串是否超过指定的长度(以字符为单位)
 *          字节
 *              StringCbCat / StringCbCatEx: 将一个字符串连接到另一个字符串
 *              StringCbCatN / StringCbCatNEx: 将指定的字节数从一个字符串连接到另一个字符串
 *              StringCbCopy / StringCbCopyEx: 将一个字符串复制到另一个字符串
 *              StringCbCopyN / StringCbCopyNEx: 将指定的字节数从一个字符串复制到另一个字符串
 *              StringCbGets / StringCbGetsEx: 从 stdin 获取一行文本，最多包括换行符 （'\n'）
 *              StringCbPrintf / StringCbPrintfEx: 将数据写入指定的字符串
 *              StringCbVPrintf / StringCbVPrintfEx: 使用指向参数列表的指针将数据写入指定字符串
 *              StringCbLength: 确定字符串是否超过指定的长度（以字节为单位）
 **/