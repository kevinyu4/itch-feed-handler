add_executable(toolchain_test toolchain_test.cpp)
target_link_libraries(toolchain_test PRIVATE GTest::gtest_main itch_warnings)

include(GoogleTest)
gtest_discover_tests(toolchain_test)
