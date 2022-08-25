#ifndef PROFILER_ELEMENT_H
#define PROFILER_ELEMENT_H
#include "framework/stopwatch.h"

enum class ProfilerElementCategory {
	RENDER,
	MISC,
};

class ProfilerElement {
private:
	std::string name;
	Stopwatch stopwatch;
	ProfilerElementCategory category;
public:
	ProfilerElement(std::string element_name, ProfilerElementCategory element_category);
	
	void begin();
	void end();
	double get_elapsed_time() const;
	std::string get_name() const;
	ProfilerElementCategory get_category() const;
};

#endif