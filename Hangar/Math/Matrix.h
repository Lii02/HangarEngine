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

	void SetIdentity();
};

#endif