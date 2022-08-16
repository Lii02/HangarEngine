#include "Precompiled.h"
#include "Color.h"

void Color::Invert() {
	this->r = 1.0f - r;
	this->g = 1.0f - g;
	this->b = 1.0f - b;
	this->a = 1.0f - a;
}

float Color::ByteToFloat(uint8_t b) {
	return b / 255.0f;
}