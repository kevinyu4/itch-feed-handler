// Toolchain test: proves the compiler, standard library and test framework
// can build and run this project.
//
// The feature checks stop the build with a clear message if the standard
// library lacks a C++23 feature the project depends on. The compiler version
// check alone is not enough: Clang uses the system's standard library, which
// can be older than the compiler.

#include <gtest/gtest.h>

#include <version>

#if !defined(__cpp_lib_byteswap) || __cpp_lib_byteswap < 202110L
#error "std::byteswap (C++23) is missing: the C++ standard library is too old (need libstdc++ from GCC 14+)"
#endif

#if !defined(__cpp_lib_expected) || __cpp_lib_expected < 202202L
#error "std::expected (C++23) is missing: the C++ standard library is too old (need libstdc++ from GCC 14+)"
#endif

TEST(Toolchain, TestFrameworkRuns) { SUCCEED(); }
