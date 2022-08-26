#ifndef DYNAMIC_LIBRARY_H
#define DYNAMIC_LIBRARY_H

class DynamicLibrary {
private:
	class Impl;
	Impl* lib_impl;
	std::string module_name;
public:
	DynamicLibrary(std::string _module_name);
	~DynamicLibrary();
	
	void* get_function(std::string function_name);
};

#endif