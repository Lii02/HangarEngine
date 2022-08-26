#ifndef COLOR_H
#define COLOR_H

struct alignas(16) Color {
	float r, g, b, a;

	Color(float _r, float _g, float _b, float _a = 1.0f);
	Color() : r(0), g(0), b(0), a(1) { }

	void invert();
	static float byte_to_float(uint8_t b);
};

#endif