cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_SUPPRESS_REGENERATION true)
# set(CMAKE_C_COMPILER gcc.exe)
# set(CMAKE_CXX_COMPILER g++.exe)

project(hangar)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)

file(GLOB_RECURSE ENGINE_SRCS src/*.cpp)
file(GLOB_RECURSE ENGINE_HDRS src/*.h)

file(GLOB_RECURSE MAIN_SRCS main/*.cpp)
file(GLOB_RECURSE MAIN_HDRS main/*.h)

if (WIN32)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
endif()

add_executable(hangar ${ENGINE_SRCS} ${ENGINE_HDRS} ${MAIN_SRCS} ${MAIN_HDRS})
target_include_directories(hangar PUBLIC "src")
target_precompile_headers(hangar PRIVATE src/precompiled.cpp PUBLIC src/precompiled.h)
target_include_directories(hangar PUBLIC "src")