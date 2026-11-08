cmake_minimum_required(VERSION 3.28)

project(itch_feed_handler LANGUAGES CXX)

# Standard C++23, not a GNU dialect, and no silent fallback to an older one.
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
# The project does not use C++20 modules. Scanning for them would make Clang
# builds need the separate clang-scan-deps tool.
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# Stop at configure time on a compiler that cannot build the project, instead
# of failing later with confusing errors deep in the code.
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  set(compiler_name "GCC")
  set(min_version 14)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  set(compiler_name "Clang")
  set(min_version 19)
else()
  message(FATAL_ERROR
    "Unsupported compiler ${CMAKE_CXX_COMPILER_ID}; build with GCC 14+ or Clang 19+")
endif()
if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS min_version)
  message(FATAL_ERROR
    "${compiler_name} ${min_version}+ required, found ${CMAKE_CXX_COMPILER_VERSION}")
endif()

# With no build type, CMake applies neither optimization nor debug info.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Warnings as errors, attached only to our own targets.
add_library(itch_warnings INTERFACE)
target_compile_options(itch_warnings INTERFACE
  -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -Wshadow -Werror)

# The checked build. Applied to everything, third-party code included, so a
# memory error is caught wherever it surfaces. Must come before any targets.
option(ENABLE_SANITIZERS "Build with AddressSanitizer and UBSan" OFF)
if(ENABLE_SANITIZERS)
  add_compile_options(
    -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endif()

# GoogleTest, pinned by version and hash. SYSTEM keeps its headers out of our
# warnings.
include(FetchContent)
FetchContent_Declare(googletest
  URL https://github.com/google/googletest/releases/download/v1.18.0/googletest-1.18.0.tar.gz
  URL_HASH SHA256=6e3191c1455468b3fc35a417fb565c1c5071aee1b7e7f85e30cf48a98d37d8b5
  SYSTEM)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)
