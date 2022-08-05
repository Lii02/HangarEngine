#ifndef HANGAR_PRECOMPILED_H
#define HANGAR_PRECOMPILED_H

#include <DirectXMath.h>
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
#include <vulkan/vulkan_win32.h>
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
#include <cstdint>

#endif