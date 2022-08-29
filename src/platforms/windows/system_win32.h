#ifndef SYSTEM_WIN32_H
#define SYSTEM_WIN32_H
#include "os/system.h"

class SystemWin32 : public System {
private:
public:
	virtual void debug_break() override;
	virtual void initialize() override;
	virtual AString get_name() override;
	virtual DynamicLibrary load_dynamic_library(AString filename) override;
	virtual void free_dynamic_library(DynamicLibrary library) override;
	virtual DynamicLibraryFunction get_library_function(AString name) override;
};

#endif