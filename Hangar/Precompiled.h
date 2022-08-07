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
#include <d3d11.h>
#include <directxtk/CommonStates.h>
#include <dxgi.h>
#include <d3dcompiler.h>
struct MessagePacket {
	HWND hwnd;
	UINT msg;
	WPARAM wParam;
	LPARAM lParam;
};
#elif __linux__
#define HANGAR_LINUX
#endif

#ifdef _DEBUG
#define HANGAR_ENABLE_ASSERT
#endif

#include <iostream>
#include <filesystem>
#include <string>
#include <vector>
#include <functional>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <cstdint>

#endif