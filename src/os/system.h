#ifndef SYSTEM_H
#define SYSTEM_H
#include "string/astring.h"

typedef void* DynamicLibrary;
typedef void (*DynamicLibraryFunc)(void*);

class System {
private:
public:
	static System* get();
	static void initialize();
	static void deinitialize();

	System();
	~System();

	void debug_break() const;
	void startup();
	AString get_name() const;
	AString get_path() const;
	int get_cpu_count() const;
	int get_ram_mb() const;
	DynamicLibrary load_dynamic_library(AString filename);
	void free_dynamic_library(DynamicLibrary library);
	DynamicLibraryFunc get_library_function(DynamicLibrary lib, AString name);
};

#endif