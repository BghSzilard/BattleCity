include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/dddb219c3eb96d7f9200f09b0a381f016e6b4562.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

file(GLOB SRC ./*.cpp)

add_executable(CoreTest ${SRC})
target_link_libraries(CoreTest GTest::gtest_main)
target_link_libraries(CoreTest GTest::gmock_main)
target_link_libraries(CoreTest Core)

include(GoogleTest)
gtest_discover_tests(CoreTest)