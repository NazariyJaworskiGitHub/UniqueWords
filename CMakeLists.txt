cmake_minimum_required(VERSION 3.12)

project(UniqueWords)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Add the source files to the project
file( GLOB srcfiles RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h *.hpp *.c *.cpp)

# Add the library for your code
add_library(${PROJECT_NAME}_lib STATIC ${srcfiles})

# Add the executable target
add_executable(${PROJECT_NAME} ${srcfiles})

# Add unit tests
add_subdirectory(ut)
