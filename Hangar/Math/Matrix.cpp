#include "Precompiled.h"
#include "Matrix.h"
#include "MathHelper.h"

Matrix::Matrix() {
	SetIdentity();
}

Matrix::Matrix(float data[16]) {
	memcpy(floatElements1D, data, 64);
}

void Matrix::SetIdentity() {
	memset(floatElements1D, 0, 64);
	floatElements2D[0][0] = 1.0f;
	floatElements2D[1][1] = 1.0f;
	floatElements2D[2][2] = 1.0f;
	floatElements2D[3][3] = 1.0f;
}

Matrix Matrix::Multiply(const Matrix& right) {
	float data[16];
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			float sum = 0.0f;
			for (int e = 0; e < 4; e++) {
				sum += floatElements1D[e + row * 4] * right.floatElements1D[col + e * 4];
			}
			data[col + row * 4] = sum;
		}
	}
	return Matrix(data);
}

Matrix Matrix::operator*(const Matrix& right) {
	return Multiply(right);
}

Matrix Matrix::operator*=(const Matrix& right) {
	*this = *this * Multiply(right);
	return *this;
}

Matrix Matrix::Translate(Vector3 position) {
	Matrix mat;
	mat.floatElements2D[3][0] = position.x;
	mat.floatElements2D[3][1] = position.y;
	mat.floatElements2D[3][2] = position.z;
	mat.floatElements2D[3][3] = 1;
	return mat;
}

Matrix Matrix::Scale(Vector3 scale) {
	Matrix mat;
	mat.floatElements2D[0][0] = scale.x;
	mat.floatElements2D[1][1] = scale.y;
	mat.floatElements2D[2][2] = scale.z;
	mat.floatElements2D[3][3] = 1;
	return mat;
}

Matrix Matrix::RotateX(float angle) {
	Matrix mat;
	mat[1][1] = cos(angle);
	mat[2][2] = cos(angle);
	mat[2][1] = -sin(angle);
	mat[1][2] = sin(angle);
	return mat;
}

Matrix Matrix::RotateY(float angle) {
	Matrix mat;
	mat[0][0] = cos(angle);
	mat[2][0] = sin(angle);
	mat[0][2] = -sin(angle);
	mat[2][2] = cos(angle);
	return mat;
}

Matrix Matrix::RotateZ(float angle) {
	Matrix mat;
	mat[0][0] = cos(angle);
	mat[1][1] = cos(angle);
	mat[1][0] = -sin(angle);
	mat[0][1] = sin(angle);
	return mat;
}

Matrix Matrix::Zero() {
	Matrix mat;
	memset(&mat, 0, 64);
	return mat;
}

Matrix Matrix::PerspectiveLH(float fov, float aspectRatio, float nearZ, float farZ) {
	Matrix matrix;
	float yScale = (1.0f / std::tan(MathHelper::DegreesToRadians(fov) / 2.0f)) * aspectRatio;
	float xScale = yScale / aspectRatio;
	float z = farZ / (farZ - nearZ);

	matrix[0][0] = xScale;
	matrix[1][1] = yScale;
	matrix[2][2] = z;
	matrix[2][3] = 1.0f;
	matrix[3][2] = -nearZ * z;
	return matrix;
}

Matrix Matrix::PerspectiveRH(float fov, float aspectRatio, float nearZ, float farZ) {
	Matrix matrix;
	float yScale = (float)((1.0f / tan(MathHelper::DegreesToRadians(fov / 2.0f))) * aspectRatio);
	float xScale = yScale / aspectRatio;
	float frustumLength = farZ - nearZ;

	matrix[0][0] = xScale;
	matrix[1][1] = yScale;
	matrix[2][2] = -((farZ + nearZ) / frustumLength);
	matrix[2][3] = -1;
	matrix[3][2] = -((2 * nearZ * farZ) / frustumLength);
	matrix[3][3] = 0;
	return matrix;
}

float* Matrix::operator[](int index) {
	return floatElements2D[index];
}