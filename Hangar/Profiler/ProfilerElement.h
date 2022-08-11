#ifndef PROFILER_ELEMENT_H
#define PROFILER_ELEMENT_H
#include "../Framework/Stopwatch.h"

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
	ProfilerElement(std::string name, ProfilerElementCategory category);
	
	void Begin();
	void End();
	double ElapsedTime() const;
	std::string GetName() const;
	ProfilerElementCategory GetCategory() const;
};

#endif