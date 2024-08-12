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
BOOL static vfsCreated = false;
DWORD static latestHookedID = 0;
usvfsParameters* p;

size_t len = 420420;
size_t* length = &len;
char dump[420420];

BOOL WINAPI usvfsWrapCreateVFS(char* Name, bool Debug, LogLevel log, CrashDumpsType type, char* dumpPath, int delay)
{
    if (vfsCreated)
    {
        if (debug)
            printf("usvfsWrapCreateVFS: already created\n");
        return false;
    }
    vfsCreated = true;
    p = usvfsCreateParameters();
    if (Debug)
        printf("usvfsWrapCreateVFS: parameters\n%s\n%d\n%d\n%d\n%s\n%d\n", Name, Debug, log, type, dumpPath, delay);
    usvfsSetInstanceName(p, Name);
    usvfsSetDebugMode(p, Debug);
    usvfsSetLogLevel(p, log);
    usvfsSetCrashDumpType(p, type);
    usvfsSetCrashDumpPath(p, dumpPath);
    usvfsSetProcessDelay(p, delay);
    usvfsCreateVFS(p);
}

void WINAPI usvfsWrapFree()
{
    if (vfsCreated)
    {
        usvfsDisconnectVFS();
        usvfsFreeParameters(p);
        vfsCreated = false;
    }
}

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
        latestHookedID = GetProcessId(pi.hProcess);
        WaitForSingleObject(pi.hProcess, INFINITE);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        return true;
    }
    else {
        printf("usvfsWrapCreateProcessHooked: Creation of process %s failed\n", lpApplicationName);
        return false;
    }
}

DWORD WINAPI usvfsWrapGetLastHookedID()
{
    return latestHookedID;
}

VOID WINAPI usvfsWrapVirtualLinkDirectoryStatic(char* source, char* destination, unsigned int flags)
{
    if (debug)
    {
        printf("usvfsWrapVirtualLinkDirectoryStatic: %s to %s.", source, destination);
        if (flags == 0x00000001)
            printf(" Flag was FAILIFEXISTS.");
        else if (flags == 0x00000002)
            printf(" Flag was MONITORCHANGES.");
        else if (flags == 0x00000004)
            printf(" Flag was CREATETARGET.");
        else if (flags == 0x00000008)
            printf(" Flag was RECURSIVE.");
        else if (flags == 0x00000010)
            printf(" Flag was FAILIFSKIPPED.");
        printf("\n");
    }
    usvfsVirtualLinkDirectoryStatic(ToW(source), ToW(destination), flags);
    return;
}

VOID WINAPI usvfsWrapVirtualLinkFile(char* source, char* destination, unsigned int flags)
{
    if (debug)
    {
        printf("usvfsWrapVirtualLinkFile: %s to %s\n", source, destination);
        if (flags == 0x00000001)
            printf(" Flag was FAILIFEXISTS.");
        else if (flags == 0x00000002)
            printf(" Flag was MONITORCHANGES.");
        else if (flags == 0x00000004)
            printf(" Flag was CREATETARGET.");
        else if (flags == 0x00000008)
            printf(" Flag was RECURSIVE.");
        else if (flags == 0x00000010)
            printf(" Flag was FAILIFSKIPPED.");
    }
        
    usvfsVirtualLinkFile(ToW(source), ToW(destination), flags);
    return;
}

BOOL WINAPI usvfsWrapCreateVFSDump(char* path)
{
    FILE* dumpFile = fopen(path, "r");
    bool createDumpFile = false;
    if (dumpFile)
        dumpFile = fopen(path, "w+");
    if (!dumpFile)
        dumpFile = fopen("usvfsWrapVFSDump.log", "w+");
    if (dumpFile)
    {
        usvfsCreateVFSDump(dump, length);
        fprintf(dumpFile, dump);
        fclose(dumpFile);
        return true;
    }
    else {
        printf("usvfsWrapCreateVFSDump: couldn't create dump\n");
        return false;
    }
}

char* WINAPI usvfsWrapReturnVFSDump()
{
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