#include "precompiled.h"
#include "matrix.h"
#include "math_helper.h"

Matrix::Matrix() {
	set_identity();
}

Matrix::Matrix(float data[16]) {
	memcpy(float_elements_1d, data, 64);
}

void Matrix::set_identity() {
	memset(float_elements_1d, 0, 64);
	float_elements_2d[0][0] = 1.0f;
	float_elements_2d[1][1] = 1.0f;
	float_elements_2d[2][2] = 1.0f;
	float_elements_2d[3][3] = 1.0f;
}

Matrix Matrix::multiply(const Matrix& right) {
	float data[16];
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			float sum = 0.0f;
			for (int e = 0; e < 4; e++) {
				sum += float_elements_1d[e + row * 4] * right.float_elements_1d[col + e * 4];
			}
			data[col + row * 4] = sum;
		}
	}
	return Matrix(data);
}

Matrix Matrix::operator*(const Matrix& right) {
	return multiply(right);
}

Matrix Matrix::operator*=(const Matrix& right) {
	*this = *this * multiply(right);
	return *this;
}

Matrix Matrix::translate(Vector3 position) {
	Matrix mat;
	mat.float_elements_2d[3][0] = position.x;
	mat.float_elements_2d[3][1] = position.y;
	mat.float_elements_2d[3][2] = position.z;
	mat.float_elements_2d[3][3] = 1;
	return mat;
}

Matrix Matrix::scale(Vector3 scale) {
	Matrix mat;
	mat.float_elements_2d[0][0] = scale.x;
	mat.float_elements_2d[1][1] = scale.y;
	mat.float_elements_2d[2][2] = scale.z;
	mat.float_elements_2d[3][3] = 1;
	return mat;
}

Matrix Matrix::rotate_x(float angle) {
	Matrix mat;
	mat[1][1] = cos(angle);
	mat[2][2] = cos(angle);
	mat[2][1] = -sin(angle);
	mat[1][2] = sin(angle);
	return mat;
}

Matrix Matrix::rotate_y(float angle) {
	Matrix mat;
	mat[0][0] = cos(angle);
	mat[2][0] = sin(angle);
	mat[0][2] = -sin(angle);
	mat[2][2] = cos(angle);
	return mat;
}

Matrix Matrix::rotate_z(float angle) {
	Matrix mat;
	mat[0][0] = cos(angle);
	mat[1][1] = cos(angle);
	mat[1][0] = -sin(angle);
	mat[0][1] = sin(angle);
	return mat;
}

Matrix Matrix::zero() {
	Matrix mat;
	memset(&mat, 0, 64);
	return mat;
}

Matrix Matrix::perspectiveLH(float fov, float aspect_ratio, float near_z, float far_z) {
	Matrix matrix;
	float yScale = (1.0f / std::tan(MathHelper::degrees_to_radians(fov) / 2.0f)) * aspect_ratio;
	float xScale = yScale / aspect_ratio;
	float z = far_z / (far_z - near_z);

	matrix[0][0] = xScale;
	matrix[1][1] = yScale;
	matrix[2][2] = z;
	matrix[2][3] = 1.0f;
	matrix[3][2] = -near_z * z;
	return matrix;
}

Matrix Matrix::perspectiveRH(float fov, float aspect_ratio, float near_z, float far_z) {
	Matrix matrix;
	float yScale = (float)((1.0f / tan(MathHelper::degrees_to_radians(fov / 2.0f))) * aspect_ratio);
	float xScale = yScale / aspect_ratio;
	float frustumLength = far_z - near_z;

	matrix[0][0] = xScale;
	matrix[1][1] = yScale;
	matrix[2][2] = -((far_z + near_z) / frustumLength);
	matrix[2][3] = -1;
	matrix[3][2] = -((2 * near_z * far_z) / frustumLength);
	matrix[3][3] = 0;
	return matrix;
}

float* Matrix::operator[](int index) {
	return float_elements_2d[index];
}