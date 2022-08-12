#ifndef ENTITY_H
#define ENTITY_H
#include "IComponent.h"

typedef uint16_t ComponentMask;

class Entity {
private:
public:
	ComponentMask componentMask;
};

#endif