#include "Precompiled.h"
#include "Matrix.h"

Matrix::Matrix() {
	SetIdentity();
}

void Matrix::SetIdentity() {
	memset(floatElements1D, 0, 64);
	floatElements2D[0][0] = 1.0f;
	floatElements2D[1][1] = 1.0f;
	floatElements2D[2][2] = 1.0f;
	floatElements2D[3][3] = 1.0f;
}