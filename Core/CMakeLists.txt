file(GLOB SRC src/*.cpp)

add_library(Core SHARED ${SRC})

target_include_directories(Core
        PUBLIC
            $<INSTALL_INTERFACE:include>
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        )