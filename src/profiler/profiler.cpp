#include "precompiled.h"
#include "profiler.h"

namespace {
	Profiler* g_profiler;
}

Profiler* Profiler::get() {
	return g_profiler;
}

void Profiler::initialize() {
	g_profiler = new Profiler();
}

void Profiler::deinitialize() {
	delete g_profiler;
}

Profiler::Profiler() {
	totals.insert(create_pair<ProfilerElementCategory, double>(ProfilerElementCategory::RENDER, 0.0));
	totals.insert(create_pair<ProfilerElementCategory, double>(ProfilerElementCategory::MISC, 0.0));
}

Profiler::~Profiler() {
}

void Profiler::clear_totals() {
	totals.set_values(0.0);
}

void Profiler::begin_profile(AString name, ProfilerElementCategory category) {
	ProfilerElement element = ProfilerElement(name, category);
	element.begin();
	elements.push(element);
}

void Profiler::end_profile() {
	ProfilerElement& element = elements.top();
	element.end();
	totals[element.get_category()] += element.get_elapsed_time();
	elements.pop();
}

double Profiler::get_total(ProfilerElementCategory category) {
	return totals[category];
}