#ifndef STOPWATCH_H
#define STOPWATCH_H

typedef std::chrono::high_resolution_clock::time_point TimePoint;

class Stopwatch {
private:
	TimePoint begin_point, end_point;
	double delta;
public:
	Stopwatch();

	void begin();
	void end();
	double get_delta_millis() const;
	double get_delta_seconds() const;
};

#endif