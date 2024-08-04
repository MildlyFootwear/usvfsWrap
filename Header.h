#pragma once

#include "pch.h"
#include <string.h>

extern "C" __declspec(dllexport) BOOL usvfsWrapCreateProcessHooked(char* lpApplicationName, char* lpCommandLine);
extern "C" __declspec(dllexport) VOID WINAPI usvfsWrapVirtualLinkDirectoryStatic(char* source, char* destination, unsigned int flags);