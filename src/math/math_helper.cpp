#include "precompiled.h"
#include "math_helper.h"

namespace MathHelper {
	float degrees_to_radians(float d) {
		return d * (PI / 180);
	}

	float radians_to_degrees(float r) {
		return r * (180 / PI);
	}
}