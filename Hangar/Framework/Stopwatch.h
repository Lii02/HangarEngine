#ifndef STOPWATCH_H
#define STOPWATCH_H

typedef std::chrono::high_resolution_clock::time_point TimePoint;

class Stopwatch {
private:
	TimePoint begin, end;
	double delta;
public:
	Stopwatch();

	void Begin();
	void End();
	double GetDeltaMillis() const;
	double GetDeltaSeconds() const;
};

#endif