#include "main.h"

/**
 * WinMain: 程序入口函数
 *      Date: 2025-08-01
 **/
int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
    HANDLE hPipe        = NULL;
    LPTSTR lpszPipename = _T("\\\\.\\pipe\\namedpipe");

    // 创建命名管道, 等待客户端连接
    for (;;) {
        hPipe = CreateNamedPipe(
            lpszPipename,               // pipe name
            PIPE_ACCESS_DUPLEX,         // read/write access
            PIPE_TYPE_MESSAGE |         // message type pipe
                PIPE_READMODE_MESSAGE | // message-read mode
                PIPE_WAIT,              // blocking mode
            PIPE_UNLIMITED_INSTANCES,   // max. instances
            BUFSIZE,                    // output buffer size
            BUFSIZE,                    // input buffer size
            0,                          // client time-out
            NULL                        // default security attribute
        );
        if (INVALID_HANDLE_VALUE == hPipe) {
            ShowLastError(_T("CreateNamedPipe"));
            return EXIT_FAILURE;
        }
        log_info(_T("Name pipe start success, pipe name: %s"), lpszPipename);

        BOOL fConnected = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
        if (fConnected) {
            log_info(_T("Client connected."));
            DWORD  dwThreadId = 0;
            HANDLE hThread    = CreateThread(
                NULL,           // no security attribute
                0,              // default stack size
                InstanceThread, // thread proc
                (LPVOID)hPipe,  // thread parameter
                0,              // not suspended
                &dwThreadId     // returns thread ID
            );
            if (hThread == NULL) {
                ShowLastError(_T("CreateThread"));
                return EXIT_FAILURE;
            } else {
                CloseHandle(hThread);
            }
        } else {
            CloseHandle(hPipe);
        }
    }

    return EXIT_SUCCESS;
}

DWORD WINAPI InstanceThread(LPVOID lpvParam) {
    HANDLE hHeap      = GetProcessHeap();
    TCHAR *pchRequest = (TCHAR *)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));
    TCHAR *pchReply   = (TCHAR *)HeapAlloc(hHeap, 0, BUFSIZE * sizeof(TCHAR));

    if (lpvParam == NULL) {
        log_info(_T("ERROR - Pipe Server Failure:"));
        log_info(_T("InstanceThread got an unexpected NULL value in lpvParam."));
        log_info(_T("InstanceThread exitting."));
        if (pchReply != NULL)
            HeapFree(hHeap, 0, pchReply);
        if (pchRequest != NULL)
            HeapFree(hHeap, 0, pchRequest);
        return EXIT_FAILURE;
    }
    if (pchRequest == NULL) {
        log_info(_T("ERROR - Pipe Server Failure:"));
        log_info(_T("InstanceThread got an unexpected NULL value in allocation."));
        log_info(_T("InstanceThread exitting."));
        if (pchReply != NULL) {
            HeapFree(hHeap, 0, pchReply);
        }
        return EXIT_FAILURE;
    }
    if (pchReply == NULL) {
        log_info(_T("ERROR - Pipe Server Failure:"));
        log_info(_T("InstanceThread got an unexpected NULL value in allocation."));
        log_info(_T("InstanceThread exitting."));
        if (pchRequest != NULL) {
            HeapFree(hHeap, 0, pchRequest);
        }
        return EXIT_FAILURE;
    }

    log_info(_T("InstanceThread created, receiving and processing messages."));

    DWORD  cbBytesRead;
    DWORD  cbReplyBytes;
    DWORD  cbWritten;
    HANDLE hPipe    = (HANDLE)lpvParam;
    BOOL   fSuccess = FALSE;
    while (1) {
        fSuccess = ReadFile(
            hPipe,                   // handle to pipe
            pchRequest,              // buffer to receive data
            BUFSIZE * sizeof(TCHAR), // size of buffer
            &cbBytesRead,            // number of bytes read
            NULL                     // not overlapped I/O
        );
        if (!fSuccess || cbBytesRead == 0) {
            if (GetLastError() == ERROR_BROKEN_PIPE) {
                log_info(_T("InstanceThread: client disconnected."));
            } else {
                log_info(_T("InstanceThread ReadFile failed, GLE=%d.\n"), GetLastError());
            }
            break;
        }
        GetAnswerToRequest(pchRequest, pchReply, &cbReplyBytes);
        fSuccess = WriteFile(
            hPipe,        // handle to pipe
            pchReply,     // buffer to write from
            cbReplyBytes, // number of bytes to write
            &cbWritten,   // number of bytes written
            NULL          // not overlapped I/O
        );
        if (!fSuccess || cbReplyBytes != cbWritten) {
            log_info(_T("InstanceThread WriteFile failed, GLE=%d.\n"), GetLastError());
            break;
        }
    }

    FlushFileBuffers(hPipe);
    DisconnectNamedPipe(hPipe);
    CloseHandle(hPipe);
    HeapFree(hHeap, 0, pchRequest);
    HeapFree(hHeap, 0, pchReply);
    log_info(_T("InstanceThread exiting."));
    return EXIT_SUCCESS;
}

VOID GetAnswerToRequest(LPTSTR pchRequest, LPTSTR pchReply, LPDWORD pchBytes) {
    log_info(_T("Client Request String: %s "), pchRequest);
    if (FAILED(StringCchCopy(pchReply, BUFSIZE, _T("default answer from server")))) {
        *pchBytes   = 0;
        pchReply[0] = 0;
        log_info(_T("StringCchCopy failed, no outgoing message."));
        return;
    }
    *pchBytes = (_tcslen(pchReply) + 1) * sizeof(TCHAR);
}