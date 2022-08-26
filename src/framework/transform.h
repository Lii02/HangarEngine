#ifndef TRANSFORM_H
#define TRANSFORM_H
#include "math/matrix.h"

struct Transform {
	Vector3 position, scale, rotation;

	Transform(Vector3 _position = {0, 0, 0}, Vector3 _scale = {1, 1, 1}, Vector3 _rotation = {0, 0, 0});

	Matrix to_matrix();
	Matrix to_view_matrix();
};

#endif