// dllmain.cpp : Defines the entry point for the DLL application.
#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex>
#include <WTypes.h>
#include <comutil.h>
#include <oleauto.h>
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

BOOL static debug = FALSE;

BOOL WINAPI usvfsWrapCreateProcessHooked(char* lpApplicationName, char* lpCommandLine)
{
    STARTUPINFOW si{ 0 };
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi{ 0 };
    if (debug)
        printf("usvfsWrapCreateProcessHooked: %s with args %s\n", lpApplicationName, lpCommandLine);
    if (usvfsCreateProcessHooked(ToW(lpApplicationName), ToW(lpCommandLine), nullptr, nullptr, TRUE, 0, 0, nullptr, &si, &pi)) {
        if (debug)
            printf("usvfsWrapCreateProcessHooked: hook success!\n");
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return true;
    }
    else {
        printf("Creation of process %s failed\n", lpApplicationName);
        return false;
    }
}

VOID WINAPI usvfsWrapVirtualLinkDirectoryStatic(char* source, char* destination, unsigned int flags)
{
    usvfsVirtualLinkDirectoryStatic(ToW(source), ToW(destination), flags);
    if (debug)
    {
        printf("usvfsWrapVirtualLinkDirectoryStatic: %s to %s.", source, destination);
        if (flags == 0x00000001)
            printf(" Flag was FAILIFEXISTS.");
        else if(flags == 0x00000002)
            printf(" Flag was MONITORCHANGES.");
        else if (flags == 0x00000004)
            printf(" Flag was CREATETARGET.");
        else if (flags == 0x00000008)
            printf(" Flag was RECURSIVE.");
        else if (flags == 0x00000010)
            printf(" Flag was FAILIFSKIPPED.");
        printf("\n");
    }
    return;
}

VOID WINAPI usvfsWrapVirtualLinkFile(char* source, char* destination, unsigned int flags)
{
    usvfsVirtualLinkFile(ToW(source), ToW(destination), flags);
    if (debug)
        printf("usvfsWrapVirtualLinkFile: %s to %s\n", source, destination);
    return;
}

char* WINAPI usvfsWrapCreateVFSDump()
{
    size_t len = 420420;
    size_t* length = &len;
    char dump[420420];
    usvfsCreateVFSDump(dump, length);
    return dump;
}

int WINAPI usvfsWrapGetHookedCount()
{
    size_t processcount = 128;
    LPDWORD processids = new DWORD;
    usvfsGetVFSProcessList(&processcount, processids);
    return processcount;
}

VOID WINAPI usvfsWrapAddSkipFileSuffix(char* fileSuffix)
{
    if (debug)
        printf("usvfsWrapAddSkipFileSuffix: %s\n", fileSuffix);
    usvfsAddSkipFileSuffix(ToW(fileSuffix));
}

VOID WINAPI usvfsWrapAddSkipDirectory(char* directory)
{
    if (debug)
        printf("usvfsWrapAddSkipDirectory: %s\n", directory);
    usvfsAddSkipDirectory(ToW(directory));
}

VOID WINAPI usvfsWrapSetDebug(BOOL b) {
    debug = b;
    printf("usvfsWrapSetDebug: Set debug to %d\n", debug);
}