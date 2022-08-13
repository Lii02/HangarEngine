#include "Precompiled.h"
#include "Transform.h"
#include "../Math/MathHelper.h"

Transform::Transform(Vector3 position, Vector3 scale, Vector3 rotation) {
	this->position = position;
	this->scale = scale;
	this->rotation = rotation;
}

Matrix Transform::ToMatrix() {
	Matrix translationMatrix, scaleMatrix, rotationMatrix;
	translationMatrix *= Matrix::Translate(position);
	scaleMatrix *= Matrix::Scale(scale);
	rotationMatrix *= Matrix::RotateX(MathHelper::DegreesToRadians(rotation.x)) * Matrix::RotateY(MathHelper::DegreesToRadians(rotation.y)) * Matrix::RotateZ(MathHelper::DegreesToRadians(rotation.z));
	return scaleMatrix * rotationMatrix * translationMatrix;
}

Matrix Transform::ToViewMatrix() {
	Matrix translationMatrix, scaleMatrix, rotationMatrix;
	translationMatrix *= Matrix::Translate(-position);
	scaleMatrix *= Matrix::Scale(scale);
	rotationMatrix *= Matrix::RotateX(MathHelper::DegreesToRadians(rotation.x)) * Matrix::RotateY(MathHelper::DegreesToRadians(rotation.y)) * Matrix::RotateZ(MathHelper::DegreesToRadians(rotation.z));
	return rotationMatrix * translationMatrix * scaleMatrix;
}