#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "../Math/Matrix.h"

struct Transform {
	Vector3 position, scale, rotation;

	Transform(Vector3 position = {0, 0, 0}, Vector3 scale = {1, 1, 1}, Vector3 rotation = {0, 0, 0});

	Matrix ToMatrix();
	Matrix ToViewMatrix();
};

#endif