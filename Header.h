#pragma once

#include "pch.h"
#include <string.h>
#include <WTypes.h>

#include "include/usvfsparameters.h"
#include "include/logging.h"

extern "C" __declspec(dllexport) BOOL WINAPI usvfsWrapCreateVFS(char* Name, bool Debug, LogLevel log, CrashDumpsType type, char* dumpPath, int delay);
extern "C" __declspec(dllexport) void WINAPI usvfsWrapFree();
extern "C" __declspec(dllexport) BOOL WINAPI usvfsWrapCreateProcessHooked(char* lpApplicationName, char* lpCommandLine, DWORD creationFlags, char* workingDir);
extern "C" __declspec(dllexport) DWORD WINAPI usvfsWrapGetLastHookedID();
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapVirtualLinkDirectoryStatic(char* source, char* destination, unsigned int flags);
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapVirtualLinkFile(char* source, char* destination, unsigned int flags);
extern "C" __declspec(dllexport) BOOL WINAPI usvfsWrapCreateVFSDump(char* path);
extern "C" __declspec(dllexport) char* WINAPI usvfsWrapReturnVFSDump();
extern "C" __declspec(dllexport) size_t WINAPI usvfsWrapGetHookedCount();
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapAddSkipFileSuffix(char* fileSuffix);
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapAddSkipDirectory(char* directory);
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapSetDebug(BOOL b);
