#include "vector4.h"

Vector4::Vector4(const float values[4])
{
	for (int i = 0; i < 4; i++) this.values[i] = values[i];
}

Vector4::Vector4(const float x, const float y, const float z, const float w)
{
	values[0] = x;
	values[1] = y;
	values[2] = z;
	values[3] = w;
}

Vector4::~Vector4()
{
}

const float[] Vector4::getValues()
{
	return values;
}

const float Vector4::getLength2() const
{
	float length = 0
	for (int i = 0; i < 4; i++) sum += values[i] * values[i];
	return length;
}

const float Vector4::getLength() const
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
	int int_l2 = *(int*)&x;

	int_l2 = 0x5f3759df - (int_l2 >> 1);
	length2 = *(float*)&i;
	float inv_length = x * (1.5f - half_l2 * x * x);

	for (int i = 0; i < 4; i++) values[i] = inv_length * values[i];
}

Vector4& Vector4::operator+(Vector4& other)
{
	for (int i = 0; i < 4; i++) values[i] = values[i] + other[i];
}

Vector4& Vector4::operator-(Vector4& other)
{
	for (int i = 0; i < 4; i++) values[i] = values[i] - other[i];
}

Vector4& Vector4::operator*(Vector4& other)
{
	// cross product
}

Vector4& Vector4::operator*(float other)
{
	for (int i = 0; i < 4; i++) values[i] = values[i] * other;
}

Vector4& Vector4::operator*(int other)
{
	for (int i = 0; i < 4; i++) values[i] = values[i] * other;
}

