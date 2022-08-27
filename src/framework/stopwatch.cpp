#include "precompiled.h"
#include "stopwatch.h"

Stopwatch::Stopwatch() {
	delta = 0;
}

void Stopwatch::begin() {
	begin_point = clock();
}

void Stopwatch::end() {
	end_point = clock();
	delta = end_point - begin_point;
}

double Stopwatch::get_delta_millis() const {
	return delta;
}

double Stopwatch::get_delta_seconds() const {
	return delta / CLOCKS_PER_SEC;
}