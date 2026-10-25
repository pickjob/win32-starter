// clang-format off
#include <stdlib.h>
#include <stddef.h>

#include <windows.h>
#include <tchar.h>
#include <strsafe.h>

#include "utils/log.h"
#include "detail_analyzer/detail_common.h"
#include "detail_analyzer/detail_export.h"
#include "detail_analyzer/detail_import.h"
// clang-format on

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
    (void)hInstance;
    (void)hPrevInstance;
    (void)lpCmdLine;
    (void)nShowCmd;
    if (log_init() != EXIT_SUCCESS) {
        return EXIT_FAILURE;
    }
    // 获得文件路径
    TCHAR lpExecutePath[MAX_PATH] = {0};
    SearchPath(NULL, _T("user32.dll"), NULL, MAX_PATH, lpExecutePath, NULL);
    // DWORD len = GetModuleFileName(NULL, lpExecutePath, MAX_PATH);
    // if (len == 0) {
    //     LOG_LAST_ERROR("GetModuleFileName");
    //     return EXIT_FAILURE;
    // }
    LOG_INFO("==================================");
    LOG_INFO("ImagePath: %ls", lpExecutePath);
    HANDLE hFile = CreateFile(lpExecutePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        LOG_LAST_ERROR("CreateFile");
        return EXIT_FAILURE;
    }
    long          nFileOffsetAddress = 0;   // FOA: file offset address
    DWORD         dwFileReadByte     = 0;   // 文件读取字节数
    LARGE_INTEGER nFileReadOffset    = {0}; // 文件读取偏移
    //
    // Dos Header
    //      IMAGE_DOS_HEADER
    //
    nFileOffsetAddress               = 0;
    nFileReadOffset.QuadPart         = nFileOffsetAddress;
    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
    IMAGE_DOS_HEADER stDosHeader = {0};
    if (FALSE == ReadFile(hFile, &stDosHeader, sizeof(stDosHeader), &dwFileReadByte, NULL)) {
        LOG_LAST_ERROR("ReadFile: IMAGE_DOS_HEADER");
        CloseHandle(hFile);
        return EXIT_FAILURE;
    }
    LOG_INFO("dosHeader.e_magic: 0x%X", stDosHeader.e_magic);
    // 0x3C: 指向NT头位置
    LOG_INFO("dosHeader.e_lfanew: 0x%X, FOA: 0x%X", stDosHeader.e_lfanew, offsetof(IMAGE_DOS_HEADER, e_lfanew));
    //
    // NT Header
    //      Signature
    //      IMAGE_FILE_HEADER
    //      IMAGE_OPTIONAL_HEADER32 / IMAGE_OPTIONAL_HEADER64
    //      IMAGE_SECTION_HEADER
    //
    nFileOffsetAddress       = stDosHeader.e_lfanew;
    nFileReadOffset.QuadPart = nFileOffsetAddress;
    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
    // NT Header -> Signature
    DWORD dwSignature = 0;
    if (FALSE == ReadFile(hFile, &dwSignature, sizeof(dwSignature), &dwFileReadByte, NULL)) {
        LOG_LAST_ERROR("ReadFile: NT Signature");
        CloseHandle(hFile);
        return EXIT_FAILURE;
    }
    LOG_INFO("ntHeaders.Signature: 0x%X, FOA: 0x%X", dwSignature, nFileOffsetAddress);
    // NT Header -> IMAGE_FILE_HEADER
    nFileOffsetAddress       = nFileOffsetAddress + sizeof(dwSignature);
    nFileReadOffset.QuadPart = nFileOffsetAddress;
    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
    IMAGE_FILE_HEADER stImageFileHeader = {0};
    if (FALSE == ReadFile(hFile, &stImageFileHeader, sizeof(stImageFileHeader), &dwFileReadByte, NULL)) {
        LOG_LAST_ERROR("ReadFile: IMAGE_FILE_HEADER");
        CloseHandle(hFile);
        return EXIT_FAILURE;
    }
    LPTSTR lpMachine = NULL;
    switch (stImageFileHeader.Machine) {
    case IMAGE_FILE_MACHINE_I386:
        lpMachine = _T("X86");
        break;
    case IMAGE_FILE_MACHINE_AMD64:
        lpMachine = _T("X86_64");
        break;
    case IMAGE_FILE_MACHINE_UNKNOWN:
    default:
        lpMachine = _T("Unknow");
        break;
    }
    LOG_INFO("ntHeaders.ImageFileHeader.Machine: 0x%X(%ls)", stImageFileHeader.Machine, lpMachine);
    TCHAR szFileHeaderCharacteristics[256] = _T("");
    if (IMAGE_FILE_EXECUTABLE_IMAGE & stImageFileHeader.Characteristics) {
        StringCchCat(szFileHeaderCharacteristics, _countof(szFileHeaderCharacteristics), _T("EXECUTABLE "));
    }
    if (IMAGE_FILE_DLL & stImageFileHeader.Characteristics) {
        StringCchCat(szFileHeaderCharacteristics, _countof(szFileHeaderCharacteristics), _T("DLL"));
    }
    if (IMAGE_FILE_LARGE_ADDRESS_AWARE & stImageFileHeader.Characteristics) {
        StringCchCat(szFileHeaderCharacteristics, _countof(szFileHeaderCharacteristics), _T("LARGE_ADDRESS "));
    }
    if (IMAGE_FILE_32BIT_MACHINE & stImageFileHeader.Characteristics) {
        StringCchCat(szFileHeaderCharacteristics, _countof(szFileHeaderCharacteristics), _T("32BIT "));
    }
    LOG_INFO("ntHeaders.ImageFileHeader.Characteristics: 0x%X(%ls)", stImageFileHeader.Characteristics, szFileHeaderCharacteristics);
    LOG_INFO("ntHeaders.ImageFileHeader.NumberOfSections: 0x%X", stImageFileHeader.NumberOfSections);
    LOG_INFO("ntHeaders.ImageFileHeader.SizeOfOptionalHeader: 0x%X", stImageFileHeader.SizeOfOptionalHeader);
    // NT Header -> IMAGE_OPTIONAL_HEADER32 / IMAGE_OPTIONAL_HEADER64
    nFileOffsetAddress       = stDosHeader.e_lfanew + sizeof(dwSignature) + sizeof(stImageFileHeader);
    nFileReadOffset.QuadPart = nFileOffsetAddress;
    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
    WORD dwOptionalHeaderMagic = 0;
    if (FALSE == ReadFile(hFile, &dwOptionalHeaderMagic, sizeof(dwOptionalHeaderMagic), &dwFileReadByte, NULL)) {
        LOG_LAST_ERROR("ReadFile: OptionalHeaderMagic");
        CloseHandle(hFile);
        return EXIT_FAILURE;
    }
    LPTSTR lpOptionalHeaderMagic = NULL;
    switch (dwOptionalHeaderMagic) {
    case IMAGE_NT_OPTIONAL_HDR32_MAGIC:
        lpOptionalHeaderMagic = _T("PE32");
        break;
    case IMAGE_NT_OPTIONAL_HDR64_MAGIC:
        lpOptionalHeaderMagic = _T("PE32+");
        break;
    default:
        lpOptionalHeaderMagic = _T("Unknow");
        break;
    }
    LOG_INFO("ntHeaders.OptionalHeader.Magic: 0x%X(%ls), FOA: 0x%X", dwOptionalHeaderMagic, lpOptionalHeaderMagic, nFileOffsetAddress);
    // 目录配置: 下标必须与 IMAGE_DATA_DIRECTORY 的 ABI 顺序严格对应, 数量固定为 IMAGE_NUMBEROF_DIRECTORY_ENTRIES(16)
    // 注: COPYRIGHT 是序号 7 在 X86 下的废弃别名, 与 ARCHITECTURE 同占一个槽位, 不可同时列出
    char *szDirectoryName[IMAGE_NUMBEROF_DIRECTORY_ENTRIES] = {
        "IMAGE_DIRECTORY_ENTRY_EXPORT",         // 0
        "IMAGE_DIRECTORY_ENTRY_IMPORT",         // 1
        "IMAGE_DIRECTORY_ENTRY_RESOURCE",       // 2
        "IMAGE_DIRECTORY_ENTRY_EXCEPTION",      // 3
        "IMAGE_DIRECTORY_ENTRY_SECURITY",       // 4
        "IMAGE_DIRECTORY_ENTRY_BASERELOC",      // 5
        "IMAGE_DIRECTORY_ENTRY_DEBUG",          // 6
        "IMAGE_DIRECTORY_ENTRY_ARCHITECTURE",   // 7
        "IMAGE_DIRECTORY_ENTRY_GLOBALPTR",      // 8
        "IMAGE_DIRECTORY_ENTRY_TLS",            // 9
        "IMAGE_DIRECTORY_ENTRY_LOAD_CONFIG",    // 10
        "IMAGE_DIRECTORY_ENTRY_BOUND_IMPORT",   // 11
        "IMAGE_DIRECTORY_ENTRY_IAT",            // 12
        "IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT",   // 13
        "IMAGE_DIRECTORY_ENTRY_COM_DESCRIPTOR", // 14
        "Reserved"                              // 15
    };
    int   nPeType            = 0;
    DWORD dwExportRva        = 0;
    DWORD dwExportSize       = 0;
    DWORD dwImportRva        = 0;
    DWORD dwImportSize       = 0;

    nFileOffsetAddress       = stDosHeader.e_lfanew + sizeof(dwSignature) + sizeof(stImageFileHeader);
    nFileReadOffset.QuadPart = nFileOffsetAddress;
    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
    if (dwOptionalHeaderMagic == IMAGE_NT_OPTIONAL_HDR32_MAGIC) {
        IMAGE_OPTIONAL_HEADER32 stOptionalHeader32 = {0};
        if (FALSE == ReadFile(hFile, &stOptionalHeader32, sizeof(stOptionalHeader32), &dwFileReadByte, NULL)) {
            LOG_LAST_ERROR("ReadFile: OptionalHeader32");
            CloseHandle(hFile);
            return EXIT_FAILURE;
        }
        LOG_INFO("ntHeaders.OptionalHeader32.Magic: 0x%X", stOptionalHeader32.Magic);
        LOG_INFO("ntHeaders.OptionalHeader32.ImageBase: 0x%X", stOptionalHeader32.ImageBase);
        LOG_INFO("ntHeaders.OptionalHeader32.SizeOfImage: 0x%X", stOptionalHeader32.SizeOfImage);
        LOG_INFO("ntHeaders.OptionalHeader32.AddressOfEntryPoint: 0x%X", stOptionalHeader32.AddressOfEntryPoint);
        LOG_INFO("ntHeaders.OptionalHeader32.BaseOfCode: 0x%X", stOptionalHeader32.BaseOfCode);
        LOG_INFO("ntHeaders.OptionalHeader32.SizeOfCode: 0x%X", stOptionalHeader32.SizeOfCode);
        LOG_INFO("ntHeaders.OptionalHeader32.SizeOfHeaders: 0x%X", stOptionalHeader32.SizeOfHeaders);
        LOG_INFO("ntHeaders.OptionalHeader32.SizeOfUninitializedData: 0x%X", stOptionalHeader32.SizeOfUninitializedData);
        LOG_INFO("ntHeaders.OptionalHeader32.SizeOfInitializedData: 0x%X", stOptionalHeader32.SizeOfInitializedData);
        LOG_INFO("ntHeaders.OptionalHeader32.SizeOfStackReserve: 0x%X", stOptionalHeader32.SizeOfStackReserve);
        LOG_INFO("ntHeaders.OptionalHeader32.SizeOfStackCommit: 0x%X", stOptionalHeader32.SizeOfStackCommit);
        LOG_INFO("ntHeaders.OptionalHeader32.SizeOfHeapReserve: 0x%X", stOptionalHeader32.SizeOfHeapReserve);
        LOG_INFO("ntHeaders.OptionalHeader32.SizeOfHeapCommit: 0x%X", stOptionalHeader32.SizeOfHeapCommit);
        LPTSTR lpSubsystem = NULL;
        switch (stOptionalHeader32.Subsystem) {
        case IMAGE_SUBSYSTEM_WINDOWS_GUI:
            lpSubsystem = _T("WindwosGUI");
            break;
        case IMAGE_SUBSYSTEM_WINDOWS_CUI:
            lpSubsystem = _T("WindwosCUI");
            break;
        case IMAGE_SUBSYSTEM_UNKNOWN:
        default:
            lpSubsystem = _T("Unknow");
            break;
        }
        LOG_INFO("ntHeaders.OptionalHeader.Subsystem: 0x%X(%ls)", stOptionalHeader32.Subsystem, lpSubsystem);
        TCHAR lpDllCharacteristics[256] = _T("");
        if (IMAGE_DLLCHARACTERISTICS_NO_SEH & stOptionalHeader32.DllCharacteristics) {
            StringCchCat(lpDllCharacteristics, _countof(lpDllCharacteristics), _T("NoSeh"));
        }
        if (IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE & stOptionalHeader32.DllCharacteristics) {
            StringCchCat(lpDllCharacteristics, _countof(lpDllCharacteristics), _T("DynamicBase"));
        }
        if (IMAGE_DLLCHARACTERISTICS_NX_COMPAT & stOptionalHeader32.DllCharacteristics) {
            StringCchCat(lpDllCharacteristics, _countof(lpDllCharacteristics), _T("NxCompat"));
        }
        LOG_INFO("ntHeaders.OptionalHeader.DllCharacteristics: 0x%X(%ls)", stOptionalHeader32.DllCharacteristics, lpDllCharacteristics);
        LOG_INFO("ntHeaders.OptionalHeader32.SectionAlignment: 0x%X", stOptionalHeader32.SectionAlignment);
        LOG_INFO("ntHeaders.OptionalHeader32.FileAlignment: 0x%X", stOptionalHeader32.FileAlignment);

        LOG_INFO("ntHeaders.OptionalHeader.NumberOfRvaAndSizes: 0x%X", stOptionalHeader32.NumberOfRvaAndSizes);
        for (DWORD i = 0; i < min(stOptionalHeader32.NumberOfRvaAndSizes, IMAGE_NUMBEROF_DIRECTORY_ENTRIES); i++) {
            LOG_INFO(
                "ntHeaders.OptionalHeader.DataDirectory[0x%X](%s).VirtualAddress: 0x%X, Size: 0x%X",
                i,
                szDirectoryName[i],
                stOptionalHeader32.DataDirectory[i].VirtualAddress,
                stOptionalHeader32.DataDirectory[i].Size
            );
            if (i == 0) {
                dwExportRva  = stOptionalHeader32.DataDirectory[i].VirtualAddress;
                dwExportSize = stOptionalHeader32.DataDirectory[i].Size;
            } else if (i == 1) {
                dwImportRva  = stOptionalHeader32.DataDirectory[i].VirtualAddress;
                dwImportSize = stOptionalHeader32.DataDirectory[i].Size;
            }
        }
        nPeType            = 0;
        nFileOffsetAddress = stDosHeader.e_lfanew + sizeof(dwSignature) + sizeof(stImageFileHeader) + sizeof(stOptionalHeader32);
    } else if (dwOptionalHeaderMagic == IMAGE_NT_OPTIONAL_HDR64_MAGIC) {
        IMAGE_OPTIONAL_HEADER64 stOptionalHeader64 = {0};
        if (FALSE == ReadFile(hFile, &stOptionalHeader64, sizeof(stOptionalHeader64), &dwFileReadByte, NULL)) {
            LOG_LAST_ERROR("ReadFile: OptionalHeader64");
            CloseHandle(hFile);
            return EXIT_FAILURE;
        }
        LOG_INFO("ntHeaders.OptionalHeader64.Magic: 0x%X", stOptionalHeader64.Magic);
        LOG_INFO("ntHeaders.OptionalHeader64.ImageBase: 0x%llX", stOptionalHeader64.ImageBase);
        LOG_INFO("ntHeaders.OptionalHeader64.SizeOfImage: 0x%X", stOptionalHeader64.SizeOfImage);
        LOG_INFO("ntHeaders.OptionalHeader64.AddressOfEntryPoint: 0x%X", stOptionalHeader64.AddressOfEntryPoint);
        LOG_INFO("ntHeaders.OptionalHeader64.BaseOfCode: 0x%X", stOptionalHeader64.BaseOfCode);
        LOG_INFO("ntHeaders.OptionalHeader64.SizeOfCode: 0x%X", stOptionalHeader64.SizeOfCode);
        LOG_INFO("ntHeaders.OptionalHeader64.SizeOfHeaders: 0x%X", stOptionalHeader64.SizeOfHeaders);
        LOG_INFO("ntHeaders.OptionalHeader64.SizeOfUninitializedData: 0x%X", stOptionalHeader64.SizeOfUninitializedData);
        LOG_INFO("ntHeaders.OptionalHeader64.SizeOfInitializedData: 0x%X", stOptionalHeader64.SizeOfInitializedData);
        LOG_INFO("ntHeaders.OptionalHeader64.SizeOfStackReserve: 0x%X", stOptionalHeader64.SizeOfStackReserve);
        LOG_INFO("ntHeaders.OptionalHeader64.SizeOfStackCommit: 0x%X", stOptionalHeader64.SizeOfStackCommit);
        LOG_INFO("ntHeaders.OptionalHeader64.SizeOfHeapReserve: 0x%X", stOptionalHeader64.SizeOfHeapReserve);
        LOG_INFO("ntHeaders.OptionalHeader64.SizeOfHeapCommit: 0x%X", stOptionalHeader64.SizeOfHeapCommit);
        LPTSTR lpSubsystem = NULL;
        switch (stOptionalHeader64.Subsystem) {
        case IMAGE_SUBSYSTEM_WINDOWS_GUI:
            lpSubsystem = _T("WindwosGUI");
            break;
        case IMAGE_SUBSYSTEM_WINDOWS_CUI:
            lpSubsystem = _T("WindwosCUI");
            break;
        case IMAGE_SUBSYSTEM_UNKNOWN:
        default:
            lpSubsystem = _T("Unknow");
            break;
        }
        LOG_INFO("ntHeaders.OptionalHeader64.Subsystem: 0x%X(%ls)", stOptionalHeader64.Subsystem, lpSubsystem);
        LPTSTR szDllCharacteristics = _T("");
        if (IMAGE_DLLCHARACTERISTICS_NO_SEH & stOptionalHeader64.DllCharacteristics) {
            StringCchCat(szDllCharacteristics, _countof(szDllCharacteristics), _T(" NoSEH "));
        } else if (IMAGE_DLLCHARACTERISTICS_DYNAMIC_BASE & stOptionalHeader64.DllCharacteristics) {
            StringCchCat(szDllCharacteristics, _countof(szDllCharacteristics), _T(" DynamicBase "));
        } else if (IMAGE_DLLCHARACTERISTICS_NX_COMPAT & stOptionalHeader64.DllCharacteristics) {
            StringCchCat(szDllCharacteristics, _countof(szDllCharacteristics), _T(" NxCompat "));
        }
        LOG_INFO("ntHeaders.OptionalHeader64.DllCharacteristics: 0x%X(%ls)", stOptionalHeader64.DllCharacteristics, szDllCharacteristics);
        LOG_INFO("ntHeaders.OptionalHeader64.SectionAlignment: 0x%X", stOptionalHeader64.SectionAlignment);
        LOG_INFO("ntHeaders.OptionalHeader64.FileAlignment: 0x%X", stOptionalHeader64.FileAlignment);

        LOG_INFO("ntHeaders.OptionalHeader64.NumberOfRvaAndSizes: 0x%X", stOptionalHeader64.NumberOfRvaAndSizes);
        for (DWORD i = 0; i < min(stOptionalHeader64.NumberOfRvaAndSizes, IMAGE_NUMBEROF_DIRECTORY_ENTRIES); i++) {
            LOG_INFO(
                "ntHeaders.OptionalHeader64.DataDirectory[%X](%s).VirtualAddress: 0x%X, Size: 0x%X",
                i,
                szDirectoryName[i],
                stOptionalHeader64.DataDirectory[i].VirtualAddress,
                stOptionalHeader64.DataDirectory[i].Size
            );
            if (i == 0) {
                dwExportRva  = stOptionalHeader64.DataDirectory[i].VirtualAddress;
                dwExportSize = stOptionalHeader64.DataDirectory[i].Size;
            } else if (i == 1) {
                dwImportRva  = stOptionalHeader64.DataDirectory[i].VirtualAddress;
                dwImportSize = stOptionalHeader64.DataDirectory[i].Size;
            }
        }
        nPeType            = 1;
        nFileOffsetAddress = stDosHeader.e_lfanew + sizeof(dwSignature) + sizeof(stImageFileHeader) + sizeof(stOptionalHeader64);
    }
    // Section Table
    //      IMAGE_SECTION_HEADER
    //      IMAGE_SECTION_DATE
    //
    IMAGE_SECTION_HEADER *lpImageSectionHeaders = malloc(sizeof(IMAGE_SECTION_HEADER) * stImageFileHeader.NumberOfSections);
    nFileReadOffset.QuadPart                    = nFileOffsetAddress;
    SetFilePointerEx(hFile, nFileReadOffset, NULL, FILE_BEGIN);
    for (int i = 0; i < stImageFileHeader.NumberOfSections; i++) {
        PIMAGE_SECTION_HEADER lpImageSectionHeader = lpImageSectionHeaders + i;
        // IMAGE_SECTION_HEADER stSectionHeader = {0};
        if (FALSE == ReadFile(hFile, lpImageSectionHeader, sizeof(IMAGE_SECTION_HEADER), &dwFileReadByte, NULL)) {
            LOG_LAST_ERROR("ReadFile: SectionHeader");
            CloseHandle(hFile);
            return EXIT_FAILURE;
        }
        TCHAR szSectionHeaderCharacteristics[256] = _T("");
        if (IMAGE_SCN_CNT_UNINITIALIZED_DATA & lpImageSectionHeader->Characteristics) {
            StringCchCat(szSectionHeaderCharacteristics, _countof(szSectionHeaderCharacteristics), _T(" UNINITIALIZED_DATA "));
        }
        if (IMAGE_SCN_CNT_INITIALIZED_DATA & lpImageSectionHeader->Characteristics) {
            StringCchCat(szSectionHeaderCharacteristics, _countof(szSectionHeaderCharacteristics), _T(" INITIALIZED_DATA "));
        }
        if (IMAGE_SCN_CNT_CODE & lpImageSectionHeader->Characteristics) {
            StringCchCat(szSectionHeaderCharacteristics, _countof(szSectionHeaderCharacteristics), _T(" CNT_CODE "));
        }
        if (IMAGE_SCN_MEM_READ & lpImageSectionHeader->Characteristics) {
            StringCchCat(szSectionHeaderCharacteristics, _countof(szSectionHeaderCharacteristics), _T(" MEM_READ "));
        }
        if (IMAGE_SCN_MEM_WRITE & lpImageSectionHeader->Characteristics) {
            StringCchCat(szSectionHeaderCharacteristics, _countof(szSectionHeaderCharacteristics), _T(" MEM_WRITE "));
        }
        if (IMAGE_SCN_MEM_EXECUTE & lpImageSectionHeader->Characteristics) {
            StringCchCat(szSectionHeaderCharacteristics, _countof(szSectionHeaderCharacteristics), _T(" MEM_EXECUTE "));
        }
        if (IMAGE_SCN_MEM_SHARED & lpImageSectionHeader->Characteristics) {
            StringCchCat(szSectionHeaderCharacteristics, _countof(szSectionHeaderCharacteristics), _T(" MEM_SHARED "));
        }
        LOG_INFO(
            "SectionData[0x%X] Name: %s, VirtualAddress: 0x%X, VirtualSize: 0x%X, PointerToRawData: 0x%X, SizeOfRawData: 0x%X, Characteristics: 0x%X(%ls)",
            i,
            lpImageSectionHeader->Name,
            lpImageSectionHeader->VirtualAddress,
            lpImageSectionHeader->Misc.VirtualSize,
            lpImageSectionHeader->PointerToRawData,
            lpImageSectionHeader->SizeOfRawData,
            lpImageSectionHeader->Characteristics,
            szSectionHeaderCharacteristics
        );
    }
    if (dwExportRva > 0 && dwExportSize > 0) {
        analyze_export(hFile, dwExportRva, dwExportSize, lpImageSectionHeaders, stImageFileHeader.NumberOfSections);
    }
    if (dwImportRva > 0 && dwImportSize > 0) {
        analyze_import(nPeType, hFile, dwImportRva, dwImportSize, lpImageSectionHeaders, stImageFileHeader.NumberOfSections);
    }
    free(lpImageSectionHeaders);

    LOG_INFO("==================================");
    CloseHandle(hFile);

    return EXIT_SUCCESS;
}