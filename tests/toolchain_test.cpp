// The compiler version check in CMakeLists.txt is not enough on its own: Clang
// uses the system's standard library, which can be older than the compiler.

#include <gtest/gtest.h>

#include <version>

#if !defined(__cpp_lib_byteswap) || __cpp_lib_byteswap < 202110L
#error "std::byteswap (C++23) is missing: the C++ standard library is too old (need libstdc++ from GCC 14+)"
#endif

#if !defined(__cpp_lib_expected) || __cpp_lib_expected < 202202L
#error "std::expected (C++23) is missing: the C++ standard library is too old (need libstdc++ from GCC 14+)"
#endif

TEST(Toolchain, TestFrameworkRuns) { SUCCEED(); }
