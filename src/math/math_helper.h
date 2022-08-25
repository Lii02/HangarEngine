#ifndef MATH_HELPER_H
#define MATH_HELPER_H

namespace MathHelper {
	constexpr float PI = 3.141592f;
	constexpr float HALF_PI = PI / 2.0f;

	float degrees_to_radians(float d);
	float radians_to_degrees(float r);
};

#endif