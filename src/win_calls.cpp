/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
#include <windows.h>
#include <string>
#include <thread>

//
extern "C"
uintptr_t loadLibrary(const char* library) {
    HANDLE hLib = LoadLibrary(library);
    return hLib == INVALID_HANDLE_VALUE ? 0 : (uintptr_t)hLib;
}
extern "C"
uintptr_t findProcessAddress(uintptr_t lib, const char* proc_name) {
    return (uintptr_t)GetProcAddress((HMODULE)lib, proc_name);
}

static int exec2(const char* cmdline, HANDLE* pstdin, HANDLE* pstdout, HANDLE* pstderr, HANDLE* pid_out, HANDLE* tid_out) {
    HANDLE childStdin_Rd = NULL;
    HANDLE childStdin_Wr = NULL;
    HANDLE childStdout_Rd = NULL;
    HANDLE childStdout_Wr = NULL;
    HANDLE childStdErr_Rd = NULL;
    HANDLE childStdErr_Wr = NULL;
    STARTUPINFO         si;
    PROCESS_INFORMATION pi;
    SECURITY_ATTRIBUTES saAttr;

    // Set the bInheritHandle flag so pipe handles are inherited. 
    saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
    saAttr.bInheritHandle = TRUE;
    saAttr.lpSecurityDescriptor = NULL;

    // Create a pipe for the child process's STDOUT. 
    if (!CreatePipe(&childStdout_Rd, &childStdout_Wr, &saAttr, 0))
        return -1;

    // Ensure the read handle to the pipe for STDOUT is not inherited.
    if (!SetHandleInformation(childStdout_Rd, HANDLE_FLAG_INHERIT, 0))
        return -1;

    // Create a pipe for the child process's STDERR. 
    if (!CreatePipe(&childStdErr_Rd, &childStdErr_Wr, &saAttr, 0))
        return -1;

    // Ensure the read handle to the pipe for STDERR is not inherited.
    if (!SetHandleInformation(childStdErr_Rd, HANDLE_FLAG_INHERIT, 0))
        return -1;

    // Create a pipe for the child process's STDIN. 
    if (!CreatePipe(&childStdin_Rd, &childStdin_Wr, &saAttr, 0))
        return -1;

    // Ensure the write handle to the pipe for STDIN is not inherited. 
    if (!SetHandleInformation(childStdin_Wr, HANDLE_FLAG_INHERIT, 0))
        return -1;

    std::unique_ptr<char[]> cmdline_m(new char[strlen(cmdline) + 1]);
    strcpy(cmdline_m.get(), cmdline);

    ZeroMemory(&si, sizeof(si));
    si.cb = sizeof(si);
    si.hStdOutput = childStdout_Wr;
    si.hStdInput = childStdin_Rd;
    si.hStdError = childStdErr_Wr;
    si.dwFlags |= STARTF_USESTDHANDLES;
    ZeroMemory(&pi, sizeof(pi));

    // Start the child process. 
    if (!CreateProcess(NULL,   // No module name (use command line)
        cmdline_m.get(),            // Command line
        NULL,               // Process handle not inheritable
        NULL,               // Thread handle not inheritable
        TRUE,              // Set handle inheritance to FALSE
        0,   // No creation flags
        NULL,               // Use parent's environment block
        NULL,               // Use parent's starting directory 
        &si,                // Pointer to STARTUPINFO structure
        &pi)               // Pointer to PROCESS_INFORMATION structure
        )
    {
        return -1;
    }

    CloseHandle(childStdin_Rd);
    CloseHandle(childStdout_Wr);
    CloseHandle(childStdErr_Wr);
    *pstdin = childStdin_Wr;
    *pstdout = childStdout_Rd;
    *pstderr = childStdErr_Rd;

    *pid_out = pi.hProcess;
    *tid_out = pi.hThread;

    return 0;
}

extern "C"
int runProcess(const char* cmd_line, const char* stdin_buffer, uint32_t stdin_size, 
    char** o_stdout_buffer, size_t* o_stdout_size, char** o_stderr_buffer, size_t* o_stderr_size) {
    HANDLE pstdin, pstdout, pstderr, pid, tid;
    int exit_code = exec2(cmd_line, &pstdin, &pstdout, &pstderr, &pid, &tid);
    if (exit_code < 0) {
        return exit_code;
    }

    std::string finaloutput;
    std::string stderroutput;
    std::thread stdout_pipereader([&]() {
        BOOL success;
        DWORD bytesread;
        do {
            char buf[4 * 1024];
            success = ReadFile(pstdout, buf, sizeof(buf), &bytesread, nullptr);
            if (success == FALSE && GetLastError() == ERROR_MORE_DATA) {
                success = TRUE;
            }
            finaloutput.append(buf, bytesread);
        } while (success);
        CloseHandle(pstdout);
    });
    std::thread stderr_pipereader([&]() {
        BOOL success;
        DWORD bytesread;
        do {
            char buf[4 * 1024];
            success = ReadFile(pstderr, buf, sizeof(buf), &bytesread, nullptr);
            if (success == FALSE && GetLastError() == ERROR_MORE_DATA) {
                success = TRUE;
            }
            stderroutput.append(buf, bytesread);
        } while (success);
        CloseHandle(pstderr);
    });

    DWORD written;
    WriteFile(pstdin, stdin_buffer, (DWORD)stdin_size, &written, nullptr);
    CloseHandle(pstdin);
    stdout_pipereader.join();
    stderr_pipereader.join();

    *o_stdout_buffer = NULL;
    *o_stdout_size = 0;
    *o_stderr_buffer = NULL;
    *o_stderr_size = 0;

    if (finaloutput.size()) {
        *o_stdout_buffer = (char*)malloc(finaloutput.size());
        *o_stdout_size = finaloutput.size();
        memset(*o_stdout_buffer, 0, finaloutput.size());
        memcpy(*o_stdout_buffer, finaloutput.c_str(), *o_stdout_size);
    }

    if (stderroutput.size()) {
        *o_stderr_buffer = (char*)malloc(stderroutput.size());
        *o_stderr_size = stderroutput.size();
        memset(*o_stderr_buffer, 0, stderroutput.size());
        memcpy(*o_stderr_buffer, stderroutput.c_str(), *o_stderr_size);
    }

    return exit_code;
}