#ifndef MATH_HELPER_H
#define MATH_HELPER_H

namespace MathHelper {
	constexpr float PI = 3.141592f;
	constexpr float HALF_PI = PI / 2.0f;

	float DegreesToRadians(float d) {
		return d * (PI / 180);
	}

	float RadiansToDegrees(float d) {
		return d * (180 / PI);
	}
};

#endif