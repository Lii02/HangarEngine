#include "precompiled.h"
#include "system.h"

namespace {
	System* g_system;
}

System* System::get() {
	return g_system;
}

void System::initialize() {
	g_system = new System;
}

void System::deinitialize() {
	delete g_system;
}

System::System() {
	startup();
}

System::~System() {
	SDL_Quit();
}

void System::debug_break() const {
	SDL_TriggerBreakpoint();
}

void System::startup() {
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_JOYSTICK);
}

AString System::get_name() const {
	return SDL_GetPlatform();
}

AString System::get_path() const {
	return SDL_GetBasePath();
}

int System::get_cpu_count() const {
	return SDL_GetCPUCount();
}

int System::get_ram_mb() const {
	return SDL_GetSystemRAM();
}

DynamicLibrary System::load_dynamic_library(AString filename) {
	return SDL_LoadObject(filename.ptr());
}

void System::free_dynamic_library(DynamicLibrary library) {
	SDL_UnloadObject(library);
}

DynamicLibraryFunc System::get_library_function(DynamicLibrary lib, AString name) {
	return (DynamicLibraryFunc)SDL_LoadFunction((void*)lib, name.ptr());
}