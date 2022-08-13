#ifndef MATH_MATRIX_H
#define MATH_MATRIX_H
#include "Vectors.h"

struct Matrix {
	union {
		struct {
			float floatElements1D[16];
		};

		struct {
			float floatElements2D[4][4];
		};

		struct {
			Vector4 arrays[4];
		};
	};

	Matrix();
	explicit Matrix(float data[16]);

	void SetIdentity();
	Matrix Multiply(const Matrix& right);
	Matrix operator*(const Matrix& right);
	Matrix operator*=(const Matrix& right);
	static Matrix Translate(Vector3 position);
	static Matrix Scale(Vector3 scale);
	static Matrix RotateX(float angle);
	static Matrix RotateY(float angle);
	static Matrix RotateZ(float angle);
	static Matrix Zero();
	static Matrix PerspectiveLH(float fov, float aspectRatio, float nearZ, float farZ);

	float* operator[](int index);
};

#endif