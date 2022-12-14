#ifndef HANGAR_PRECOMPILED_H
#define HANGAR_PRECOMPILED_H

#ifdef _MSC_VER
#define HANGAR_API __declspec(dllexport)
#else
#define HANGAR_API
#endif

#ifdef _WIN32
#define HANGAR_WINDOWS
#elif __linux__
#define HANGAR_LINUX
#endif

#ifdef _DEBUG
#define HANGAR_ENABLE_ASSERT
#define HANGAR_FORCE_INLINE
#else
#ifdef _MSC_VER
#define POLARIS_FORCE_INLINE __forceinline
#else
#define POLARIS_FORCE_INLINE ((always_inline)) inline
#endif
#endif

#define HANGAR_BIT(x) (1 << x)
#define HANGAR_ARRAYSIZE(arr) (sizeof(*arr) / sizeof(arr))

#include <SDL2/SDL.h>
#undef main

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#endif