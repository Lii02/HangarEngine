#include "precompiled.h"
#include "profiler_element.h"

ProfilerElement::ProfilerElement(std::string element_name, ProfilerElementCategory element_category) {
	name = element_name;
	category = element_category;
}

void ProfilerElement::begin() {
	stopwatch.Begin();
}

void ProfilerElement::end() {
	stopwatch.End();
}

double ProfilerElement::get_elapsed_time() const {
	return stopwatch.GetDeltaSeconds();
}

std::string ProfilerElement::get_name() const {
	return name;
}

ProfilerElementCategory ProfilerElement::get_category() const {
	return category;
}