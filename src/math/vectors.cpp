#include "Precompiled.h"
#include "Vectors.h"

// Vector2
Vector2::Vector2(float _x, float _y) {
	x = _x;
	y = _y;
}

Vector2::Vector2(float v) {
	x = v;
	y = v;
}

Vector2::Vector2(float* arr) {
	x = arr[0];
	y = arr[1];
}

float Vector2::length() const {
	return sqrtf(x * x + y * y);
}

float Vector2::length_squared() const {
	return x * x + y * y;
}

Vector2 Vector2::normalized() {
	float l = length();
	return Vector2(x / l, y / l);
}

void Vector2::normalize() {
	float l = length();
	x /= l;
	y /= l;
}

Vector2 Vector2::operator-() {
	return Vector2(-x, -y);
}

Vector2 Vector2::operator+() {
	return Vector2(+x, +y);
}

// Vector3
Vector3::Vector3(float _x, float _y, float _z) {
	x = _x;
	y = _y;
	z = _z;
}

Vector3::Vector3(float v) {
	x = v;
	y = v;
	z = v;
}

Vector3::Vector3(float* arr) {
	x = arr[0];
	y = arr[1];
	z = arr[2];
}

float Vector3::length() const {
	return sqrtf(x * x + y * y + z * z);
}

float Vector3::length_squared() const {
	return x * x + y * y + z * z;
}

Vector3 Vector3::normalized() {
	float l = length();
	return Vector3(x / l, y / l, z / l);
}

void Vector3::normalize() {
	float l = length();
	x /= l;
	y /= l;
	z /= l;
}

Vector3 Vector3::operator-() {
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator+() {
	return Vector3(+x, +y, +z);
}

// Vector4
Vector4::Vector4(float _x, float _y, float _z, float _w) {
	x = _x;
	y = _y;
	z = _z;
	w = _w;
}

Vector4::Vector4(float v) {
	x = v;
	y = v;
	z = v;
	w = v;
}

Vector4::Vector4(float* arr) {
	x = arr[0];
	y = arr[1];
	z = arr[2];
	w = arr[3];
}

float Vector4::length() const {
	return sqrtf(x * x + y * y + z * z + w * w);
}

float Vector4::length_squared() const {
	return x * x + y * y + z * z + w * w;
}

Vector4 Vector4::normalized() {
	float l = length();
	return Vector4(x / l, y / l, z / l, w / l);
}

void Vector4::normalize() {
	float l = length();
	x /= l;
	y /= l;
	z /= l;
	w /= l;
}

Vector4 Vector4::operator-() {
	return Vector4(-x, -y, -z, -w);
}

Vector4 Vector4::operator+() {
	return Vector4(+x, +y, +z, +w);
}