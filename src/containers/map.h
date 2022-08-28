#ifndef MAP_H
#define MAP_H
#include "containers/pair.h"
#include "containers/list.h"
#include "hash/hashing.h"

template <typename K>
struct DefaultMapComparator {
	bool operator()(const K& left, const K& right) {
		return left < right;
	}
};

template <typename K>
struct DefaultMapHash {
	uint64_t operator()(const K& key, size_t num_buckets) {
		return key % num_buckets;
	}
};

template <typename K, typename V, class Comp = DefaultMapComparator<K>, class Hash = DefaultMapHash<K>>
class Map {
public:
	typedef Pair<K, V> MapPair;
private:
	List<MapPair>* tables;
	size_t num_buckets;
	Hash hash_function;
	Comp comparator_function;
public:
	Map(size_t _num_buckets = 1) {
		num_buckets = _num_buckets;
		tables = new List<MapPair>[_num_buckets];
	}

	~Map() {
		free_data();
	}

	void free_data() {
		if(tables)
			delete[] tables;
	}

	void insert(MapPair pair) {
		uint64_t hash = hash_function(pair.first, num_buckets);
		List<MapPair>& list = tables[hash];
		for (auto it = list.begin(); it != list.end(); it++) {
			MapPair& iterator_pair = *it;
			if (comparator_function(pair.first, iterator_pair.first)) {
				iterator_pair.second = pair.second;
				return;
			}
		}
		list.insert(list.begin(), pair);
	}

	bool erase(MapPair pair) {
		uint64_t hash = hash_function(pair.first, num_buckets);
		List<MapPair>& list = tables[hash];
		for (auto it = list.begin(); it != list.end(); it++) {
			MapPair& iterator_pair = *it;
			if (pair.first == iterator_pair.first) {
				list.erase(it);
				return true;
			}
		}
		return false;
	}

	V* find(const K& key) {
		uint64_t hash = hash_function(key, num_buckets);
		List<MapPair>& list = tables[hash];
		for (auto it = list.begin(); it != list.end(); ++it) {
			MapPair& pair = *it;
			if (pair.first == key) {
				return &pair.second;
			}
		}
		return nullptr;
	}

	V& operator[](const K& key) {
		V* v = find(key);
		return *v;
	}

	const V& operator[](const K& key) const {
		V* v = find(key);
		return *v;
	}

	void set_values(const V& value) {
		for (size_t i = 0; i < num_buckets; i++) {
			List<MapPair>& list = tables[i];
			for (auto it = list.begin(); it != list.end(); ++it) {
				MapPair& pair = *it;
				pair.second = value;
			}
		}
	}
};

#endif