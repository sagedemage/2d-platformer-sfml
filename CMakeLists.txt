cmake_minimum_required(VERSION 3.22 VERSION 0.1.0)

project(2dPlatformer)

set(HEADER_FILES src/pch/sfml-pch.hpp)

set(SOURCE_FILES 
    src/main.cpp 
    ${HEADER_FILES}
    )

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(STANDARD_CXX_VERSION_FLAG "-std=c++11")
set(OPTIMIZE_FLAG "-O3")
set(WARNING_FLAGS "-Werror -Wpedantic -Wall -Wextra -Wno-unknown-pragmas")

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} ${STANDARD_C_VERSION_FLAG} ${OPTIMIZE_FLAG} ${WARNING_FLAGS}")

add_executable(2dPlatformer ${SOURCE_FILES})

find_package(SFML 2.5 COMPONENTS window graphics system audio REQUIRED)

target_link_libraries(2dPlatformer -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio)

target_precompile_headers(2dPlatformer PRIVATE ${HEADER_FILES})
