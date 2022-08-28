#ifndef MAP_H
#define MAP_H

template <typename F, typename S>
class Map {
public:
	struct Node {
		F first;
		S second;
		Node* next, *prev;
	};
private:
	Node* first, *last;
public:
};

#endif