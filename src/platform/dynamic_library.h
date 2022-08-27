#ifndef DYNAMIC_LIBRARY_H
#define DYNAMIC_LIBRARY_H
#include "string/astring.h"

class DynamicLibrary {
private:
	class Impl;
	Impl* lib_impl;
	AString module_name;
public:
	DynamicLibrary(AString _module_name);
	~DynamicLibrary();
	
	void* get_function(AString function_name);
};

#endif