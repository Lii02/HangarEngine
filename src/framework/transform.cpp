#include "precompiled.h"
#include "transform.h"
#include "math/math_helper.h"

Transform::Transform(Vector3 tposition, Vector3 tscale, Vector3 trotation) {
	position = tposition;
	scale = tscale;
	rotation = trotation;
}

Matrix Transform::to_matrix() {
	Matrix translation_matrix, scale_matrix, rotation_matrix;
	translation_matrix *= Matrix::translate(position);
	scale_matrix *= Matrix::scale(scale);
	rotation_matrix *= Matrix::rotate_x(MathHelper::degrees_to_radians(rotation.x)) * Matrix::rotate_y(MathHelper::degrees_to_radians(rotation.y)) * Matrix::rotate_z(MathHelper::degrees_to_radians(rotation.z));
	return scale_matrix * rotation_matrix * translation_matrix;
}

Matrix Transform::to_view_matrix() {
	Matrix translation_matrix, scale_matrix, rotation_matrix;
	translation_matrix *= Matrix::translate(-position);
	scale_matrix *= Matrix::scale(scale);
	rotation_matrix *= Matrix::rotate_x(MathHelper::degrees_to_radians(rotation.x)) * Matrix::rotate_y(MathHelper::degrees_to_radians(rotation.y)) * Matrix::rotate_z(MathHelper::degrees_to_radians(rotation.z));
	return rotation_matrix * translation_matrix * scale_matrix;
}