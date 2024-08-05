// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex>
#include <WTypes.h>
#include <comutil.h>
#include "oleauto.h"
#include "pch.h"
#include "Header.h"
#include "include/usvfs.h"
#include "include/usvfsparameters.h"
#include "include/logging.h"

wchar_t* ToW(const char* charArray)
{

    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
    return wString;

}

BOOL WINAPI usvfsWrapCreateProcessHooked(char* lpApplicationName, char* lpCommandLine)
{
    STARTUPINFOW si{ 0 };
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{ 0 };

    if (usvfsCreateProcessHooked(ToW(lpApplicationName), ToW(lpCommandLine), nullptr, nullptr, TRUE, 0, 0, nullptr, &si, &pi)) {

        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return true;
    }
    else {
        printf("\nCreation of process %s failed", lpApplicationName);
        return false;
    }
}

VOID WINAPI usvfsWrapVirtualLinkDirectoryStatic(char* source, char* destination, unsigned int flags)
{
    usvfsVirtualLinkDirectoryStatic(ToW(source), ToW(destination), flags);
}

VOID WINAPI usvfsWrapVirtualLinkFile(char* source, char* destination, unsigned int flags)
{
    usvfsVirtualLinkDirectoryStatic(ToW(source), ToW(destination), flags);
}

BSTR WINAPI usvfsWrapCreateVFSDump()
{
    size_t len = 69420;
    size_t* length = &len;
    char dump[69420];
    usvfsCreateVFSDump(dump, length);
    BSTR result = NULL;
    int lenA = lstrlenA(dump);
    int lenW = ::MultiByteToWideChar(CP_ACP, 0, dump, lenA, NULL, 0);
    if (lenW > 0)
    {
        result = ::SysAllocStringLen(0, lenW);
        ::MultiByteToWideChar(CP_ACP, 0, dump, lenA, result, lenW);
    }
    return result;
    //return ANSItoBSTR(dump);
}