#ifndef PIECEVIEW_H
#define PIECEVIEW_H

#include "3dmath/matrix4.h"

class PieceView
{
private:
	Vector4 minOriginal;
	Vector4 maxOriginal;
	Vector4 normalsOriginal[3];

	Vector4 minTransformed;
	Vector4 maxTransformed;
	Vector4 normalsTransformed[3];

	Matrix4 transform;

	void applyTransform();

public:
	PieceView();
	~PieceView();

	enum Face{FRONT, BACK, UP, DOWN, LEFT, RIGHT, NONE};

	void setTransform(Matrix4 transform);
	Vector4& getMin(bool applyTransform);
	Vector4& getMax(bool applyTransform);
	Vector4 (*getNormals(bool applyTransform))[3];
	Face getIntersectionFace();

};

#endif // PIECEVIEW_H
