#ifndef PROFILER_H
#define PROFILER_H
#include "ProfilerElement.h"

class Profiler {
private:
	std::stack<ProfilerElement> elements;
	std::map<ProfilerElementCategory, double> totals;
public:
	static Profiler*& Get();
	static void Initialize();
	static void DeInitialize();

	Profiler();
	~Profiler();
	Profiler(const Profiler&) = delete;

	void ClearTotals();
	void BeginProfile(std::string name, ProfilerElementCategory category);
	void EndFunction();
	double GetTotal(ProfilerElementCategory category);
};

#endif