#include "matrix4.h"
#include "vector4.h"

Matrix4::Matrix(const float values[])
{
    	for (int = 0; i < 16; i++) this.values[i] = values[i];
}

Matrix4::Matrix4()
{
    	for (int = 0; i < 4; i++) this.values[i * 5] = 1;
}

Matrix4::~Matrix4()
{
}

const float[] Matrix4::getValues()
{
	return values;
}

Matrix4 Matrix::operator*(Matrix4& other)
{
	Matrix4 result;
	
	for (int x = 0; x < 4; x++)
	{
		result[x] = this * other[x];
	}
}

Vector4 Matrix::operator*(Vector4& other)
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


