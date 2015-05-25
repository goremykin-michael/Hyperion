#pragma once

// Windows includes
#if PLATFORM == PLATFORM_WIN32
#include <windows.h>
#include <windowsx.h>

// Linux includes
#elif PLATFORM == PLATFORM_LINUX
#include <dlfcn.h>

#endif

// Hyperion includes
#include <Core/Common/HnTypes.h>
#include <Core/Text/HnString.h>

// Spiral defines
#define HnInline inline 
#define HnForceInline __forceinline
#define HnNullPointer 0

#if PLATFORM == PLATFORM_WIN32
#define HnShared __declspec(dllexport)

#endif