#include "precompiled.h"
#include "system.h"
#ifdef HANGAR_WINDOWS
#include "platforms/windows/system_win32.h"
#endif

namespace {
	System* g_system;
}

System* System::get() {
	return g_system;
}

void System::initialize() {
#ifdef HANGAR_WINDOWS
	g_system = new SystemWin32();
#endif
}

void System::deinitialize() {
	delete g_system;
}