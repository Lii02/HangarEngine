#ifndef RANDOMGEN_H
#define RANDOMGEN_H

template <typename T>
class RandomGen {
private:
	uint32_t seed;
	std::random_device dev;
	T min_val, max_val;
	std::mt19937* engine;
	std::uniform_real_distribution<T> dist;
public:
	RandomGen(T minVal = 0, T maxVal = 1) {
		engine = new std::mt19937(dev());
		set_limits(minVal, maxVal);
		set_seed(static_cast<uint32_t>(time(nullptr)));
	}

	~RandomGen() {
		delete engine;
	}

	RandomGen(const RandomGen&) = delete;

	void set_limits(T new_min_val, T new_max_val) {
		minVal = new_min_val;
		maxVal = new_max_val;
		dist = std::uniform_real_distribution<T>(new_min_val, new_max_val);
	}

	void set_seed(uint32_t new_seed) {
		seed = new_seed;
		engine->seed(new_seed);
	}

	uint32_t get_default_seed() const {
		return engine->default_seed;
	}

	T generate() const {
		return dist(*engine);
	}
};

#endif