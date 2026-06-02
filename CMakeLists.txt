cmake_minimum_required(VERSION 3.10)

project(FloatConverter)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(converter main.cpp)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Choose the type of build." FORCE)
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(converter PRIVATE -O3 -march=native -mtune=native)
    target_link_options(converter PRIVATE -static -static-libgcc -static-libstdc++)
elseif(MSVC)
    target_compile_options(converter PRIVATE /O2 /Ob2 /Oi)
endif()

