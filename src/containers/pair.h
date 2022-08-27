#ifndef PAIR_H
#define PAIR_H

template <typename F, typename S>
struct Pair {
	F first;
	S second;

	inline void delete_first() {
		delete first;
		first = nullptr;
	}

	inline void delete_second() {
		delete second;
		second = nullptr;
	}

	inline void delete_pair() {
		delete_first();
		delete_second();
	}
};

template <typename F, typename S>
Pair<F, S> create_pair(F first, S second) {
	Pair<F, S> p;
	p.first = first;
	p.second = second;
	return p;
}

#endif