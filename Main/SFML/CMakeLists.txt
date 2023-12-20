option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)
 
set(SRC
    src/Source.cpp
    src/Game.cpp 
    src/SFMLMenu.cpp
    src/TileMap.cpp
    src/Timer.cpp
    src/TextureManager.cpp
    src/SFMLBullet.cpp
)

add_executable(IS_BattleCity ${SRC})

target_link_libraries(IS_BattleCity PRIVATE Core)

target_link_libraries(IS_BattleCity PRIVATE sfml-graphics sfml-window sfml-system)

if(WIN32)
    add_custom_command(
        TARGET IS_BattleCity
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:IS_BattleCity>
        VERBATIM)
endif()

install(TARGETS IS_BattleCity)

file(COPY assets/ DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/sfml_assets)