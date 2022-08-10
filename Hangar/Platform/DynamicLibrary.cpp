#include "Precompiled.h"
#include "DynamicLibrary.h"

#ifdef HANGAR_WINDOWS
class DynamicLibrary::Impl {
private:
	HMODULE dll;
public:
	Impl(const char* moduleName) {
		this->dll = LoadLibraryA(moduleName);
	}

	~Impl() {
		FreeLibrary(dll);
	}

	void* GetFunction(const char* functionName) {
		return GetProcAddress(dll, functionName);
	}
};
#endif

DynamicLibrary::DynamicLibrary(std::string moduleName) {
	this->moduleName = moduleName;
	this->libImpl = new Impl(moduleName.c_str());
}

DynamicLibrary::~DynamicLibrary() {
	delete libImpl;
}

void* DynamicLibrary::GetFunction(std::string functionName) {
	return libImpl->GetFunction(functionName.c_str());
}