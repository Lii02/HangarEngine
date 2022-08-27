#ifndef PROFILER_ELEMENT_H
#define PROFILER_ELEMENT_H
#include "framework/stopwatch.h"
#include "string/astring.h"

enum class ProfilerElementCategory {
	RENDER,
	MISC,
};

class ProfilerElement {
private:
	AString name;
	Stopwatch stopwatch;
	ProfilerElementCategory category;
public:
	ProfilerElement() = default;
	ProfilerElement(AString _name, ProfilerElementCategory _category);
	
	void begin();
	void end();
	double get_elapsed_time() const;
	AString get_name() const;
	ProfilerElementCategory get_category() const;
};

#endif