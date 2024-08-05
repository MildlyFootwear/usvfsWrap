#pragma once

#include "pch.h"
#include <string.h>
#include <WTypes.h>

extern "C" __declspec(dllexport) BOOL usvfsWrapCreateProcessHooked(char* lpApplicationName, char* lpCommandLine);
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapVirtualLinkDirectoryStatic(char* source, char* destination, unsigned int flags);
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapVirtualLinkFile(char* source, char* destination, unsigned int flags);
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapCreateVFSDump();
extern "C" __declspec(dllexport) int WINAPI usvfsWrapGetHookedCount();
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapAddSkipFileSuffix(char* fileSuffix);
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapAddSkipDirectory(char* directory);
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapSetDebug(BOOL b);