cmake_minimum_required(VERSION 3.4)
project(UtilBucket VERSION 0.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


option(BUILD_TEST "Built the different test cases" OFF)
option(BUILD_BENCHMARK "Built the different benchmarks" OFF)
option(ENABLE_DEBUG_SYMBOLS "Built debug symbols to use in external tools like Vallgrind" OFF)
option(ENABLE_OPTIMIZATIONS "Enable all the compiler optimizations" ON)

# Enable all warnings
if (CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
elseif(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()


# Define the macro to check if we are in release/debug mode
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  -DNDEBUG")

if (ENABLE_DEBUG_SYMBOLS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}  -g")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}  -g")
endif()

if (ENABLE_OPTIMIZATIONS)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
endif()


if (BUILD_TEST)
    add_subdirectory(test)

endif()

if (BUILD_BENCHMARK)
    add_subdirectory(benchmark)
endif()

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/meta/)
target_sources(${PROJECT_NAME} INTERFACE ${PROJECT_SOURCE_DIR}/meta/)


add_executable(${PROJECT_NAME}-exe main.cpp)
