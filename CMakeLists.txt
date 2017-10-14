cmake_minimum_required(VERSION 3.8)
project(cpp17challenge)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(cpp17challenge src/main.cpp)
target_link_libraries(cpp17challenge stdc++fs)
add_subdirectory(tests)

