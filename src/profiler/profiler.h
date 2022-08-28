#ifndef PROFILER_H
#define PROFILER_H
#include "profiler_element.h"
#include "containers/stack.h"
#include "containers/map.h"

class Profiler {
private:
	Stack<ProfilerElement> elements;
	Map<ProfilerElementCategory, double> totals;
public:
	static Profiler* get();
	static void initialize();
	static void deinitialize();

	Profiler();
	~Profiler();
	Profiler(const Profiler&) = delete;

	void clear_totals();
	void begin_profile(AString name, ProfilerElementCategory category);
	void end_profile();
	double get_total(ProfilerElementCategory category);
};

#endif