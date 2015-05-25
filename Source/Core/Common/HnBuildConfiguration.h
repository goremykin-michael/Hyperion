#pragma once

#define PLATFORM_WIN32   1
#define PLATFORM_LINUX   2
#define PLATFORM_APPLE   3
#define PLATFORM_XBOX360 4
#define PLATFORM_PS3     5

#define CONSOLE_APPLICATION 1
#define GUI_APPLICATION 2

#define COMPILER_MSVC 1
#define COMPILER_GNUC 2
#define COMPILER_BORL 3

#define ARCHITECTURE_32 1
#define ARCHITECTURE_64 2

// finds the compiler type and version
#if defined( _MSC_VER )
#   define COMPILER COMPILER_MSVC
#   define COMP_VER _MSC_VER

#elif defined( __GNUC__ )
#   define COMPILER COMPILER_GNUC
#   define COMP_VER (((__GNUC__)*100) + \
	(__GNUC_MINOR__*10) + \
	__GNUC_PATCHLEVEL__)

#elif defined( __BORLANDC__ )
#   define COMPILER COMPILER_BORL
#   define COMP_VER __BCPLUSPLUS__

#else
#   pragma error "No known compiler. Abort!"

#endif

// check if we can use __forceinline or if we need to use __inline instead
#if COMPILER == COMPILER_MSVC
#   if COMP_VER >= 1200
#       define FORCEINLINE __forceinline
#   endif
#elif defined(__MINGW32__)
#   if !defined(FORCEINLINE)
#       define FORCEINLINE __inline
#   endif
#else
#   define FORCEINLINE __inline
#endif

// finds the current platform
#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( WIN32 )
#   define PLATFORM PLATFORM_WIN32

#elif defined( __APPLE_CC__)
#   define PLATFORM PLATFORM_APPLE

#else
#   #   pragma error "No known platform. Abort!"
#endif

// find the arch type
#if defined(__x86_64__) || defined(_M_X64) || defined(__powerpc64__) || defined(__alpha__) || defined(__ia64__) || defined(__s390__) || defined(__s390x__)
#   define ARCH_TYPE ARCHITECTURE_64
#else
#   define ARCH_TYPE ARCHITECTURE_32
#endif

//----------------------------------------------------------------------------
// Windows Settings
#if PLATFORM == PLATFORM_WIN32

// Win32 compilers use _DEBUG for specifying debug builds.
#   ifdef _DEBUG
#       define DEBUG_MODE 1
#   else
#       define DEBUG_MODE 0
#   endif

#endif

//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
// Linux/Apple Settings
#if PLATFORM == PLATFORM_LINUX || PLATFORM == PLATFORM_APPLE

#   ifdef DEBUG
#       define DEBUG_MODE 1
#   else
#       define DEBUG_MODE 0
#   endif

#endif