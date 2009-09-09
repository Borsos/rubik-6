class Matrix4
{
private:
	float values [16];

public:
	Matrix4(const float values[16]);
	Matrix4();
	~Matrix4();
	
	const float[16] getValues();

	Matrix4& operator* (Matrix4& other);
	Vector4& operator* (Vector4& other);
}

