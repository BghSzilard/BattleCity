set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

set(SRC
    src/Source.cpp
    src/Game.cpp
    src/Map.cpp
    src/Timer.cpp
)

add_executable(IS_BattleCity ${SRC})
target_link_libraries(IS_BattleCity PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(IS_BattleCity PRIVATE cxx_std_17)

if(WIN32)
    add_custom_command(
        TARGET IS_BattleCity
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:IS_BattleCity>
        VERBATIM)
endif()

install(TARGETS IS_BattleCity)