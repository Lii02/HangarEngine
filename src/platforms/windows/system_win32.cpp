#include "precompiled.h"
#include "system_win32.h"
#include <windows.h>

void SystemWin32::debug_break() {
	DebugBreak();
}

void SystemWin32::initialize() {
}

AString SystemWin32::get_name() {
	return "Windows";
}

DynamicLibrary SystemWin32::load_dynamic_library(AString filename) {
    return DynamicLibrary();
}

void SystemWin32::free_dynamic_library(DynamicLibrary library) {
}

DynamicLibraryFunction SystemWin32::get_library_function(AString name) {
    return DynamicLibraryFunction();
}