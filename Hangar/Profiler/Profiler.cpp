#include "Precompiled.h"
#include "Profiler.h"

namespace {
	Profiler* g_Profiler;
}

Profiler*& Profiler::Get() {
	return g_Profiler;
}

void Profiler::Initialize() {
	g_Profiler = new Profiler();
}

void Profiler::DeInitialize() {
	delete g_Profiler;
}

Profiler::Profiler() {
	totals.emplace(ProfilerElementCategory::RENDER, 0.0);
	totals.emplace(ProfilerElementCategory::MISC, 0.0);
}

Profiler::~Profiler() {
}

void Profiler::ClearTotals() {
	for (auto& val : totals) {
		val.second = 0.0;
	}
}

void Profiler::BeginProfile(std::string name, ProfilerElementCategory category) {
	ProfilerElement element = ProfilerElement(name, category);
	element.Begin();
	elements.push(element);
}

void Profiler::EndFunction() {
	ProfilerElement& element = elements.top();
	element.End();
	totals[element.GetCategory()] += element.ElapsedTime();
	elements.pop();
}

double Profiler::GetTotal(ProfilerElementCategory category) {
	return totals[category];
}