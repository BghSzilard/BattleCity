cmake_minimum_required(VERSION 3.25)

project(IS_BattleCity LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

enable_testing()

add_subdirectory(Core)
add_subdirectory(Core/tests)
add_subdirectory(Main)
