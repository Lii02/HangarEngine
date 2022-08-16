#include "Precompiled.h"
#include "Color.h"

Color::Color(float r, float g, float b, float a) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

void Color::Invert() {
	this->r = 1.0f - r;
	this->g = 1.0f - g;
	this->b = 1.0f - b;
	this->a = 1.0f - a;
}

float Color::ByteToFloat(uint8_t b) {
	return b / 255.0f;
}