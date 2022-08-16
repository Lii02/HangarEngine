#ifndef COLOR_H
#define COLOR_H

struct Color {
	float r, g, b, a;

	Color(float r, float g, float b, float a = 1.0f);
	Color() : r(0), g(0), b(0), a(1) { }

	void Invert();
	static float ByteToFloat(uint8_t b);
};

#endif