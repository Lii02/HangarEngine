#ifndef HANGAR_PRECOMPILED_H
#define HANGAR_PRECOMPILED_H

#include <vulkan/vulkan.h>

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
#include <vulkan/vulkan_win32.h>
struct MessagePacket {
	HWND hwnd;
	UINT msg;
	WPARAM wParam;
	LPARAM lParam;
};
#elif __linux__
#define HANGAR_LINUX
#endif

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <cassert>

#endif