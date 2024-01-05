file(GLOB SRC ./*.cpp)

add_executable(CoreTest ${SRC})
target_link_libraries(CoreTest GTest::gtest_main)
target_link_libraries(CoreTest Core)

include(GoogleTest)
gtest_discover_tests(CoreTest)