#include "Precompiled.h"
#include "MathHelper.h"

namespace MathHelper {
	float DegreesToRadians(float d) {
		return d * (PI / 180);
	}

	float RadiansToDegrees(float r) {
		return r * (180 / PI);
	}
}