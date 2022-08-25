#ifndef MATH_VECTORS_H
#define MATH_VECTORS_H

typedef float Vector1;

#define VECTOR2_BINARY_OPERATOR_OVERLOAD(Op) \
		inline Vector2 operator Op (Vector2 with) \
		{ \
			return Vector2(x Op with.x, y Op with.y); \
		} \

#define VECTOR3_BINARY_OPERATOR_OVERLOAD(Op) \
		inline Vector3 operator Op (Vector3 with) \
		{ \
			return Vector3(x Op with.x, y Op with.y, z Op with.z); \
		} \

#define VECTOR4_BINARY_OPERATOR_OVERLOAD(Op) \
		inline Vector4 operator Op (Vector4 with) \
		{ \
			return Vector4(x Op with.x, y Op with.y, z Op with.z, w Op with.w); \
		} \

struct Vector2 {
	float x;
	float y;

	Vector2() : x(0), y(0) { }
	Vector2(float vx, float vy);
	explicit Vector2(float v);
	explicit Vector2(float* arr);

	float length() const;
	float length_squared() const;
	Vector2 normalized();
	void normalize();

	Vector2 operator-();
	Vector2 operator+();
	VECTOR2_BINARY_OPERATOR_OVERLOAD(-);
	VECTOR2_BINARY_OPERATOR_OVERLOAD(-=);
	VECTOR2_BINARY_OPERATOR_OVERLOAD(+);
	VECTOR2_BINARY_OPERATOR_OVERLOAD(+=);
	VECTOR2_BINARY_OPERATOR_OVERLOAD(*);
	VECTOR2_BINARY_OPERATOR_OVERLOAD(*=);
	VECTOR2_BINARY_OPERATOR_OVERLOAD(/);
	VECTOR2_BINARY_OPERATOR_OVERLOAD(/=);
};

struct Vector3 {
	float x;
	float y;
	float z;

	Vector3() : x(0), y(0), z(0) { }
	Vector3(float vx, float vy, float vz);
	explicit Vector3(float v);
	explicit Vector3(float* arr);

	float length() const;
	float length_squared() const;
	Vector3 normalized();
	void normalize();

	Vector3 operator-();
	Vector3 operator+();
	VECTOR3_BINARY_OPERATOR_OVERLOAD(-);
	VECTOR3_BINARY_OPERATOR_OVERLOAD(-= );
	VECTOR3_BINARY_OPERATOR_OVERLOAD(+);
	VECTOR3_BINARY_OPERATOR_OVERLOAD(+= );
	VECTOR3_BINARY_OPERATOR_OVERLOAD(*);
	VECTOR3_BINARY_OPERATOR_OVERLOAD(*= );
	VECTOR3_BINARY_OPERATOR_OVERLOAD(/ );
	VECTOR3_BINARY_OPERATOR_OVERLOAD(/= );
};

struct Vector4 {
	float x;
	float y;
	float z;
	float w;

	Vector4() : x(0), y(0), z(0), w(0) { }
	Vector4(float vx, float vy, float vz, float vw);
	explicit Vector4(float v);
	explicit Vector4(float* arr);

	float length() const;
	float length_squared() const;
	Vector4 normalized();
	void normalize();

	Vector4 operator-();
	Vector4 operator+();
	VECTOR4_BINARY_OPERATOR_OVERLOAD(-);
	VECTOR4_BINARY_OPERATOR_OVERLOAD(-=);
	VECTOR4_BINARY_OPERATOR_OVERLOAD(+);
	VECTOR4_BINARY_OPERATOR_OVERLOAD(+=);
	VECTOR4_BINARY_OPERATOR_OVERLOAD(*);
	VECTOR4_BINARY_OPERATOR_OVERLOAD(*=);
	VECTOR4_BINARY_OPERATOR_OVERLOAD(/);
	VECTOR4_BINARY_OPERATOR_OVERLOAD(/=);
};

typedef Vector4 Quaternion;

#include "vertex_types.h"
#include "mesh_data_3d.h"

#endif