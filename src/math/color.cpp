#include "Precompiled.h"
#include "Color.h"

Color::Color(float _r, float _g, float _b, float _a) {
	r = _r;
	g = _g;
	b = _b;
	a = _a;
}

void Color::invert() {
	r = 1.0f - r;
	g = 1.0f - g;
	b = 1.0f - b;
	a = 1.0f - a;
}

float Color::byte_to_float(uint8_t b) {
	return b / 255.0f;
}