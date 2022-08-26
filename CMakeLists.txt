cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)
set(CMAKE_SUPPRESS_REGENERATION true)

project(hangar)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)

file(GLOB_RECURSE ENGINE_SRCS src/*.cpp)
file(GLOB_RECURSE ENGINE_HDRS src/*.h)

file(GLOB_RECURSE SANDBOX_SRCS sandbox/*.cpp)
file(GLOB_RECURSE SANDBOX_HDRS sandbox/*.h)

if (WIN32)
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MD")
endif()

add_library(hangar STATIC ${ENGINE_SRCS} ${ENGINE_HDRS})
target_precompile_headers(hangar PRIVATE src/precompiled.cpp PUBLIC src/precompiled.h)
target_include_directories(hangar PUBLIC "src")

add_executable(sandbox ${SANDBOX_SRCS} ${SANDBOX_HDRS})
target_include_directories(sandbox PUBLIC "src")
target_link_libraries(sandbox hangar)