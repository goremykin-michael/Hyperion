# Install script for directory: D:/Projects/llvm_3.61/RELEASE_361/rc1/tools

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

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("D:/Projects/llvm_3.61.build/tools/llvm-config/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/opt/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-as/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-dis/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-mc/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llc/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-ar/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-nm/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-size/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-cov/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-profdata/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-link/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/lli/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-extract/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-diff/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/macho-dump/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-objdump/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-readobj/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-rtdyld/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-dwarfdump/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/dsymutil/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-vtabledump/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/bugpoint/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/bugpoint-passes/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-bcanalyzer/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-stress/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-mcmarkup/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/verify-uselistorder/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-symbolizer/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-c-test/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/obj2yaml/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/yaml2obj/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-go/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/lto/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/llvm-lto/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/gold/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/clang/cmake_install.cmake")
  include("D:/Projects/llvm_3.61.build/tools/msbuild/cmake_install.cmake")

endif()

