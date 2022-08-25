#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H
#include "Vectors.h"

struct Matrix {
	union {
		struct {
			float float_elements_1d[16];
		};

		struct {
			float float_elements_2d[4][4];
		};

		struct {
			Vector4 arrays[4];
		};
	};

	Matrix();
	explicit Matrix(float data[16]);

	void set_identity();
	Matrix multiply(const Matrix& right);
	Matrix operator*(const Matrix& right);
	Matrix operator*=(const Matrix& right);
	static Matrix translate(Vector3 position);
	static Matrix scale(Vector3 scale);
	static Matrix rotate_x(float angle);
	static Matrix rotate_y(float angle);
	static Matrix rotate_z(float angle);
	static Matrix zero();
	static Matrix perspectiveLH(float fov, float aspect_ratio, float near_z, float far_z);
	static Matrix perspectiveRH(float fov, float aspect_ratio, float near_z, float far_z);

	float* operator[](int index);
};

#endif