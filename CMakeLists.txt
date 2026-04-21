cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)

project(MyProject LANGUAGES CXX)

find_package(Qt6 6.10.2 EXACT REQUIRED COMPONENTS Core Gui Widgets)
find_package(Python3 3.12.10 EXACT REQUIRED COMPONENTS Interpreter Development.Embed)
find_package(fmt 12.1.0 EXACT REQUIRED)

add_library(MyOptions INTERFACE)
target_compile_options(MyOptions INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:-W4;-permissive-;-Zc:__cplusplus>
)
target_compile_definitions(MyOptions INTERFACE
    $<$<CXX_COMPILER_ID:MSVC>:NOMINMAX>)

link_libraries(MyOptions)

add_subdirectory(src/core)
add_subdirectory(src/ui)

add_executable(main src/main.cpp)
target_link_libraries(main PRIVATE
    Qt6::Widgets
    Python3::Python
    fmt::fmt
    MyProject::core
    MyProject::ui
)