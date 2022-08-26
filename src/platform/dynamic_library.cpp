#include "precompiled.h"
#include "dynamic_library.h"

#ifdef HANGAR_WINDOWS
class DynamicLibrary::Impl {
private:
	HMODULE dll;
public:
	Impl(const char* module_name) {
		dll = LoadLibraryA(module_name);
	}

	~Impl() {
		FreeLibrary(dll);
	}

	void* get_function(const char* function_name) {
		return GetProcAddress(dll, function_name);
	}
};
#endif

DynamicLibrary::DynamicLibrary(std::string _module_name) {
	module_name = _module_name;
	lib_impl = new Impl(_module_name.c_str());
}

DynamicLibrary::~DynamicLibrary() {
	delete lib_impl;
}

void* DynamicLibrary::get_function(std::string function_name) {
	return lib_impl->get_function(function_name.c_str());
}