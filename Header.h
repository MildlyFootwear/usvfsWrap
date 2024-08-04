#pragma once

#include "pch.h"
#include <string.h>

extern "C" __declspec(dllexport) BOOL usvfsWrapCreateProcessHooked(char* lpApplicationName, char* lpCommandLine);