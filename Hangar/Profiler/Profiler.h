#ifndef PROFILER_H
#define PROFILER_H
#include "ProfilerElement.h"

class Profiler {
private:
	std::stack<ProfilerElement> elements;
	std::map<std::string, double> totals;
public:
	static Profiler& Get();

	Profiler();
	~Profiler();
	Profiler(const Profiler&) = delete;

	void BeginProfile(std::string name, ProfilerElementCategory category);
	void EndFunction();
	double GetTotal(std::string name);
};

#endif