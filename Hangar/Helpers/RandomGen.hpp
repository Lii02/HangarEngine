#ifndef RANDOMGEN_H
#define RANDOMGEN_H

template <typename T>
class RandomGen {
private:
	uint32_t seed;
	std::random_device dev;
	T minVal, maxVal;
	std::mt19937* engine;
	std::uniform_real_distribution<T> dist;
public:
	RandomGen(T minVal = 0, T maxVal = 1) {
		this->engine = new std::mt19937(dev());
		SetLimits(minVal, maxVal);
		SetSeed(static_cast<uint32_t>(time(nullptr)));
	}

	~RandomGen() {
		delete engine;
	}

	RandomGen(const RandomGen&) = delete;

	void SetLimits(T minVal, T maxVal) {
		this->minVal = minVal;
		this->maxVal = maxVal;
		this->dist = std::uniform_real_distribution<T>(minVal, maxVal);
	}

	void SetSeed(uint32_t newSeed) {
		this->seed = newSeed;
		engine->seed(newSeed);
	}

	uint32_t GetDefaultSeed() const {
		return engine->default_seed;
	}

	T Generate() const {
		return dist(*engine);
	}
};

#endif