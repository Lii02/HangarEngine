#ifndef HANGAR_PRECOMPILED_H
#define HANGAR_PRECOMPILED_H

#ifdef _MSC_VER
#define HANGAR_API __declspec(dllexport)
#elif
#define HANGAR_API
#endif

#ifdef _WIN32
#define HANGAR_WINDOWS
#define NOGDI
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Windowsx.h>
#undef UINT
#undef INT
#undef FLOAT
#undef min
#undef max
struct MessagePacket {
	HWND hwnd;
	UINT msg;
	WPARAM w_param;
	LPARAM l_param;
};
#elif __linux__
#define HANGAR_LINUX
#endif

#ifdef _DEBUG
#define HANGAR_ENABLE_ASSERT
#endif

#define HANGAR_BIT(x) (1 << x)
#define HANGAR_ARRAYSIZE(arr) (sizeof(*arr) / sizeof(arr))

#include <filesystem>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>
#include <chrono>
#include <random>
#include <stack>
#include <map>
#include <queue>

#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

#include "helpers/random_gen.hpp"

#endif