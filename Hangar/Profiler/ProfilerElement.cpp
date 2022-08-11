#include "Precompiled.h"
#include "ProfilerElement.h"

ProfilerElement::ProfilerElement(std::string name, ProfilerElementCategory category) {
	this->name = name;
	this->category = category;
}

void ProfilerElement::Begin() {
	stopwatch.Begin();
}

void ProfilerElement::End() {
	stopwatch.End();
}

double ProfilerElement::ElapsedTime() const {
	return stopwatch.GetDeltaSeconds();
}

std::string ProfilerElement::GetName() const {
	return name;
}

ProfilerElementCategory ProfilerElement::GetCategory() const {
	return category;
}