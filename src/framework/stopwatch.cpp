#include "precompiled.h"
#include "stopwatch.h"

Stopwatch::Stopwatch() {
	delta = 0;
}

void Stopwatch::begin() {
	begin_point = std::chrono::high_resolution_clock::now();
}

void Stopwatch::end() {
	end_point = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> deltaDuration = end_point - begin_point;
	delta = deltaDuration.count();
}

double Stopwatch::get_delta_millis() const {
	return delta;
}

double Stopwatch::get_delta_seconds() const {
	return delta / 1000;
}