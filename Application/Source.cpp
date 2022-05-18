// Application.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <Windows.h>
#include <WinUser.h>
#include <iostream>



HWND GetConsoleHwnd(void)
{
    HWND hwndFound;
    SetConsoleTitle(L"geek");
    Sleep(40);
    hwndFound = FindWindow(NULL, L"geek");
    SetConsoleTitle(L"some");
    return(hwndFound);
}

int main()
{
    HMODULE myDLL;
    HWND hConsole;
    myDLL = LoadLibrary(L".\\DLL.dll");
    if (!myDLL)
        std::cout << "LoadLibrary Failed ";
    printf("I live forever\n");
    hConsole = GetConsoleHwnd();
    ShowWindow(hConsole, SW_HIDE);
    while (1) {
        // infinite loop to keep thread alive.
    }
}


