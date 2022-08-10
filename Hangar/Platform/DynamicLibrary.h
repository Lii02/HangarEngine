#ifndef DYNAMIC_LIBRARY_H
#define DYNAMIC_LIBRARY_H

class DynamicLibrary {
private:
	class Impl;
	Impl* libImpl;
	std::string moduleName;
public:
	DynamicLibrary(std::string moduleName);
	~DynamicLibrary();
	
	void* GetFunction(std::string functionName);
};

#endif