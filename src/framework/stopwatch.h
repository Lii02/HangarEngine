#ifndef STOPWATCH_H
#define STOPWATCH_H

class Stopwatch {
private:
	clock_t begin_point, end_point;
	double delta;
public:
	Stopwatch();

	void begin();
	void end();
	double get_delta_millis() const;
	double get_delta_seconds() const;
};

#endif