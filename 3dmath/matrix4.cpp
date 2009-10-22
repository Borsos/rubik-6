#include "matrix4.h"
#include "vector4.h"

Matrix4::Matrix4(float values[16])
{
    	for (int i = 0; i < 16; i++) this->values[i] = values[i];
}

Matrix4::Matrix4()
{
    	for (int i = 0; i < 4; i++) this->values[i * 5] = 1;
}

Matrix4::~Matrix4()
{
}

float* Matrix4::getValues()
{
	return values;
}

Vector4& Matrix4::operator[](int i)
{
	Vector4 tmp;
	return tmp;
}

Matrix4 Matrix4::operator*(Matrix4& other)
{
	Matrix4 result;
	
	for (int x = 0; x < 4; x++)
	{
		result[x] = (*this) * (other[x]);
	}

	return result;
}

Vector4 Matrix4::operator*(Vector4& other)
{
	Vector4 result;

	for (int y = 0; y < 4; y++)
	{
		result[y] = 0;
		for (int x = 0; x < 4; x++)
		{
			result[y] += values[y + x];
		}
	}
	
	return result;
}


