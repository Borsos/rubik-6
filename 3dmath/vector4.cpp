#include <cmath>
#include "vector4.h"

Vector4::Vector4(float values[4])
{
	for (int i = 0; i < 4; i++) this->values[i] = values[i];
}

Vector4::Vector4(float x, float y, float z, float w)
{
	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = w;
}

Vector4::Vector4()
{
	//*this = Vector4(0, 0, 0, 0);
}

Vector4::~Vector4()
{
}

float* Vector4::getValues()
{
	return values;
}

float Vector4::getLength2()
{
	return (*this) * (*this);
}

float Vector4::getLength()
{
	return sqrt(getLength2());
}

void Vector4::normalizeExact()
{
	float length = getLength();
	for (int i = 0; i < 4; i++) values[i] = values[i] / length;	
}

void Vector4::normalizeFast()
{
	float length2 = getLength2();
	float half_l2 = 0.5f * length2;
	int int_l2 = *(int*)&length2;

	int_l2 = 0x5f3759df - (int_l2 >> 1);
	length2 = *(float*)&int_l2;
	float inv_length = length2 * (1.5f - half_l2 * length2 * length2);

	for (int i = 0; i < 4; i++) values[i] = inv_length * values[i];
}

float& Vector4::operator[](int i)
{
	return values[i];
}

Vector4 Vector4::operator+(Vector4& other)
{
	Vector4 tmp;
	for (int i = 0; i < 4; i++) tmp[i] = values[i] + other[i];
	return tmp;
}

Vector4 Vector4::operator-(void)
{
	Vector4 tmp;
	for (int i = 0; i < 4; i++) tmp[i] = -values[i];
	return tmp;
}

Vector4 Vector4::operator-(Vector4& other)
{
	Vector4 tmp;
	for (int i = 0; i < 4; i++) values[i] = values[i] - other[i];
	return tmp;
}

float Vector4::operator*(Vector4& other) // dot product
{
	float length2 = 0;
	for (int i = 0; i < 4; i++) length2 += values[i] * other[i];
	return length2;
}

Vector4 Vector4::operator*(float other)
{
	Vector4 tmp;
	for (int i = 0; i < 4; i++) tmp[i] = values[i] * other;
	return tmp;
}

Vector4 Vector4::operator*(int other)
{
	Vector4 tmp;
	for (int i = 0; i < 4; i++) tmp[i] = values[i] * other;
	return tmp;
}

Vector4 Vector4::operator/(Vector4& other) // cross product
{
	Vector4 tmp;
	return tmp;
}

