#include "precompiled.h"
#include "system.h"

namespace {
	System* g_system;
}

System* System::get() {
	return g_system;
}

void System::set_global_system(System* system) {
	g_system = system;
}

void System::deinitialize() {
	delete g_system;
}