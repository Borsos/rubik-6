#ifndef QUATERNION_H
#define QUATERNION_H

#include "vector4.h"
#include "matrix4.h"

class Quaternion : public Vector4
{
public:
	Quaternion(const float values[4]):Vector4(values);
	Quaternion(float one, float i, float j, float k):Vector4(one, i, j, k);

	Matrix4 getRotationMatrix();
};

#endif // QUATERNION_H

