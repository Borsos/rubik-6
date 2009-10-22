#ifndef MATRIX4_H
#define MATRIX4_H

#include "vector4.h"

class Matrix4
{
private:
	float values [16];

public:
	Matrix4(float values[16]);
	Matrix4();
	~Matrix4();
	
	float* getValues();

	Vector4& operator[](int i);
	Matrix4 operator*(Matrix4& other);
	Vector4 operator*(Vector4& other);
};

#endif // MATRIX4_H
