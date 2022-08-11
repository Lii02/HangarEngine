#include "Precompiled.h"
#include "Profiler.h"

namespace {
	Profiler g_Profiler;
}

Profiler& Profiler::Get() {
	return g_Profiler;
}

Profiler::Profiler() {
	totals.emplace("Render", 0.0);
	totals.emplace("Misc", 0.0);
}

Profiler::~Profiler() {
}

void Profiler::BeginProfile(std::string name, ProfilerElementCategory category) {
	ProfilerElement element = ProfilerElement(name, category);
	element.Begin();
	elements.push(element);
}

void Profiler::EndFunction() {
	ProfilerElement& element = elements.top();
	element.End();
	totals[element.GetName()] += element.ElapsedTime();
	elements.pop();
}

double Profiler::GetTotal(std::string name) {
	return totals[name];
}