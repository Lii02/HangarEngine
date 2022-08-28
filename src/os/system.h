#ifndef SYSTEM_H
#define SYSTEM_H
#include "string/astring.h"

typedef void* DynamicLibrary;
typedef void (*DynamicLibraryFunction)(void*);

class System {
private:
public:
	static System* get();
	static void set_global_system(System* system);
	static void deinitialize();

	virtual ~System() { }

	virtual void debug_break() = 0;
	virtual void initialize() = 0;
	virtual AString get_name() = 0;
	virtual DynamicLibrary load_dynamic_library(AString filename) = 0;
	virtual void free_dynamic_library(DynamicLibrary library) = 0;
	virtual DynamicLibraryFunction get_library_function(AString name) = 0;
};

#endif