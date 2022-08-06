#include "Precompiled.h"
#include "Vectors.h"

// Vector2
Vector2::Vector2(float x, float y) {
	this->x = x;
	this->y = y;
}

Vector2::Vector2(float v) {
	this->x = v;
	this->y = v;
}

Vector2::Vector2(float* arr) {
	this->x = arr[0];
	this->y = arr[1];
}

float Vector2::Length() const {
	return std::sqrtf(x * x + y * y);
}

float Vector2::LengthSquared() const {
	return x * x + y * y;
}

Vector2 Vector2::Normalized() {
	float l = Length();
	return Vector2(x / l, y / l);
}

void Vector2::Normalize() {
	float l = Length();
	this->x /= l;
	this->y /= l;
}

Vector2 Vector2::operator-() {
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+() {
	return Vector2(+x, +y);
}

// Vector3
Vector3::Vector3(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector3::Vector3(float v) {
	this->x = v;
	this->y = v;
	this->z = v;
}

Vector3::Vector3(float* arr) {
	this->x = arr[0];
	this->y = arr[1];
	this->z = arr[2];
}

float Vector3::Length() const {
	return std::sqrtf(x * x + y * y + z * z);
}

float Vector3::LengthSquared() const {
	return x * x + y * y + z * z;
}

Vector3 Vector3::Normalized() {
	float l = Length();
	return Vector3(x / l, y / l, z / l);
}

void Vector3::Normalize() {
	float l = Length();
	this->x /= l;
	this->y /= l;
	this->z /= l;
}

Vector3 Vector3::operator-() {
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+() {
	return Vector3(+x, +y, +z);
}

// Vector4
Vector4::Vector4(float x, float y, float z, float w) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->w = w;
}

Vector4::Vector4(float v) {
	this->x = v;
	this->y = v;
	this->z = v;
	this->w = v;
}

Vector4::Vector4(float* arr) {
	this->x = arr[0];
	this->y = arr[1];
	this->z = arr[2];
	this->w = arr[3];
}

float Vector4::Length() const {
	return std::sqrtf(x * x + y * y + z * z + w * w);
}

float Vector4::LengthSquared() const {
	return x * x + y * y + z * z + w * w;
}

Vector4 Vector4::Normalized() {
	float l = Length();
	return Vector4(x / l, y / l, z / l, w / l);
}

void Vector4::Normalize() {
	float l = Length();
	this->x /= l;
	this->y /= l;
	this->z /= l;
	this->w /= l;
}

Vector4 Vector4::operator-() {
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator+() {
	return Vector4(+x, +y, +z, +w);
}