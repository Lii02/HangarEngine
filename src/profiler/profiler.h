#ifndef PROFILER_H
#define PROFILER_H
#include "profiler_element.h"

class Profiler {
private:
	std::stack<ProfilerElement> elements;
	std::map<ProfilerElementCategory, double> totals;
public:
	static Profiler*& get();
	static void initialize();
	static void deinitialize();

	Profiler();
	~Profiler();
	Profiler(const Profiler&) = delete;

	void clear_totals();
	void begin_profile(AString name, ProfilerElementCategory category);
	void end_function();
	double get_total(ProfilerElementCategory category);
};

#endif