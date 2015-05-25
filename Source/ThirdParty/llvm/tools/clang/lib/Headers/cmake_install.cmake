# Install script for directory: D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files/LLVM")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/clang/3.6.1/include" TYPE FILE PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ FILES
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/adxintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/altivec.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/ammintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/arm_acle.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/avx2intrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/avx512bwintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/avx512erintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/avx512fintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/avx512vlbwintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/avx512vlintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/avxintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/bmi2intrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/bmiintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/cpuid.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/emmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/f16cintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/float.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/fma4intrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/fmaintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/ia32intrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/immintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/Intrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/iso646.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/limits.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/lzcntintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/mm3dnow.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/mmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/mm_malloc.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/module.modulemap"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/nmmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/pmmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/popcntintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/prfchwintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/rdseedintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/rtmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/shaintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/smmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/stdalign.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/stdarg.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/stdatomic.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/stdbool.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/stddef.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/__stddef_max_align_t.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/stdint.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/stdnoreturn.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/tbmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/tgmath.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/tmmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/unwind.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/vadefs.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/varargs.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/__wmmintrin_aes.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/wmmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/__wmmintrin_pclmul.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/x86intrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/xmmintrin.h"
    "D:/Projects/llvm_3.61/RELEASE_361/rc1/tools/clang/lib/Headers/xopintrin.h"
    "D:/Projects/llvm_3.61.build/tools/clang/lib/Headers/arm_neon.h"
    )
endif()

