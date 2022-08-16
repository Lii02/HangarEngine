#ifndef COLOR_H
#define COLOR_H

struct Color {
	float r, g, b, a;

	Color() : r(0), g(0), b(0), a(0) { }

	void Invert();
	static float ByteToFloat(uint8_t b);
};

#endif