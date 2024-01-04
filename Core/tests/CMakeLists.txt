enable_testing()

add_executable(CoreTest hello_test.cpp)
target_link_libraries(CoreTest GTest::gtest_main)
target_link_libraries(CoreTest Core)

include(GoogleTest)
gtest_discover_tests(CoreTest)