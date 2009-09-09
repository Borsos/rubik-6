class Vector4
{
private:
	float values[4];
	const float getLength2();

public:
	Vector4(const float values[4]);
	Vector4(float x, float y, float z, float w);
	~Vector4();

	const float[4] getValues();
	const float getLength();
	void normalize();

	float& operator[] (int i);
	Vector4& operator+ (Vector4& other);
	Vector4& operator- (Vector4& other);
	Vector4& operator* (Vector4& other);
	Vector4& operator* (float other);
	Vector4& operator* (int other);
};
