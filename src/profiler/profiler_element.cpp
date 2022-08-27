#include "precompiled.h"
#include "profiler_element.h"

ProfilerElement::ProfilerElement(AString _name, ProfilerElementCategory _category) {
	name = _name;
	category = _category;
}

void ProfilerElement::begin() {
	stopwatch.begin();
}

void ProfilerElement::end() {
	stopwatch.end();
}

double ProfilerElement::get_elapsed_time() const {
	return stopwatch.get_delta_seconds();
}

AString ProfilerElement::get_name() const {
	return name;
}

ProfilerElementCategory ProfilerElement::get_category() const {
	return category;
}