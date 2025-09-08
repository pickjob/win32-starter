#include "main.h"

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    // 连接命令管道
    LPTSTR lpszPipename = _T("\\\\.\\pipe\\namedpipe");
    HANDLE hPipe;
    while (1) {
        hPipe = CreateFile(
            lpszPipename,                 // pipe name
            GENERIC_READ | GENERIC_WRITE, // read and write access
            0,                            // no sharing
            NULL,                         // default security attributes
            OPEN_EXISTING,                // opens existing pipe
            0,                            // default attributes
            NULL                          // no template file
        );

        if (INVALID_HANDLE_VALUE != hPipe) {
            break;
        }
        if (!WaitNamedPipe(lpszPipename, 20000)) {
            log_info(_T("Could not open pipe: 20 second wait timed out."));
            return EXIT_FAILURE;
        }
    }
    DWORD dwMode   = PIPE_READMODE_MESSAGE;
    BOOL  fSuccess = SetNamedPipeHandleState(
        hPipe,   // pipe handle
        &dwMode, // new pipe mode
        NULL,    // don't set maximum bytes
        NULL     // don't set maximum time
    );
    if (!fSuccess) {
        ShowLastError(_T("SetNamedPipeHandleState"));
        return EXIT_FAILURE;
    }

    // 发送消息
    LPTSTR lpvMessage = _T("Default message from client.");
    DWORD  cbToWrite  = (_tcslen(lpvMessage) + 1) * sizeof(TCHAR);
    log_info(_T("Sending %d byte message: \"%s\"\n"), cbToWrite, lpvMessage);
    DWORD cbWritten;
    fSuccess = WriteFile(
        hPipe,      // pipe handle
        lpvMessage, // message
        cbToWrite,  // message length
        &cbWritten, // bytes written
        NULL        // not overlapped
    );
    if (!fSuccess) {
        ShowLastError(_T("WriteFile"));
        return EXIT_FAILURE;
    }

    // 接收消息
    log_info(_T("Message sent to server, receiving reply as follows:"));
    TCHAR chBuf[BUFSIZE];
    DWORD cbRead;
    do {
        fSuccess = ReadFile(
            hPipe,                   // pipe handle
            chBuf,                   // buffer to receive reply
            BUFSIZE * sizeof(TCHAR), // size of buffer
            &cbRead,                 // number of bytes read
            NULL                     // not overlapped
        );
        if (!fSuccess && GetLastError() != ERROR_MORE_DATA) {
            break;
        }
        log_info(_T("%s"), chBuf);
    } while (!fSuccess); // repeat loop if ERROR_MORE_DATA
    if (!fSuccess) {
        log_info(_T("ReadFile from pipe failed. GLE=%d\n"), GetLastError());
        return -1;
    }

    // 结束
    CloseHandle(hPipe);

    return EXIT_SUCCESS;
}