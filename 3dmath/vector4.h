#ifndef VECTOR4_H
#define VECTOR4_H

class Vector4
{
private:
	float values[4];
	float getLength2();

public:
	Vector4(float values[4]);
	Vector4(float x, float y, float z, float w);
	Vector4();
	~Vector4();

	float* getValues();
	float getLength();
	void normalizeExact();
	void normalizeFast();

	float& operator[](int i);
	Vector4 operator+(Vector4& other);
	Vector4 operator-(void);
	Vector4 operator-(Vector4& other);
	float operator*(Vector4& other);
	Vector4 operator*(float other);
	Vector4 operator*(int other);
	Vector4 operator/(Vector4& other);
};

#endif // VECTOR4_H

