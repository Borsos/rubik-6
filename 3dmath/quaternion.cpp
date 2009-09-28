#include "quaternion.h"

Quaternion::Quaternion()
{
}

Quaternion::Quaternion()
{
}

Quaternion::Quaternion()
{
}

Quaternion::~Quaternion()
{
}

Quaternion::getRotation()
{
	float rotation[16];

	rotation[0] = values[0];
	rotation[1] = values[1];
	rotation[2] = values[2];
	rotation[3] = values[3];

	rotation[4] = -values[1];
	rotation[5] = values[0];
	rotation[6] = -values[3];
	rotation[7] = values[2];

	rotation[8] = -values[2];
	rotation[9] = values[3];
	rotation[10] = values[0];
	rotation[11] = -values[1];

	rotation[12] = -values[3];
	rotation[13] = -values[2];
	rotation[14] = values[1];
	rotation[15] = values[0];

	return Matrix4(rotation);
}

