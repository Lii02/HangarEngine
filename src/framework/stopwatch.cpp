#include "Precompiled.h"
#include "Stopwatch.h"

Stopwatch::Stopwatch() {
	this->delta = 0;
}

void Stopwatch::Begin() {
	this->begin = std::chrono::high_resolution_clock::now();
}

void Stopwatch::End() {
	this->end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> deltaDuration = end - begin;
	delta = deltaDuration.count();
}

double Stopwatch::GetDeltaMillis() const {
	return delta;
}

double Stopwatch::GetDeltaSeconds() const {
	return delta / 1000;
}