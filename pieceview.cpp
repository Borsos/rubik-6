#include "pieceview.h"

PieceView::PieceView(): minOriginal(-1.0f, -1.0f, -1.0f, 1.0f), maxOriginal(1.0f, 1.0f, 1.0f, 1.0f)
{
	for (int i = 0; i < 3; i++)
	{
		normalsOriginal[i] = Vector4(0, 0, 0, 0);
		normalsOriginal[i][i] = maxOriginal[i] - minOriginal[i];
		normalsOriginal[i].normalizeFast();
	}
}

PieceView::~PieceView()
{
}

void PieceView::applyTransform()
{
	minTransformed = transform * minOriginal;
	maxTransformed = transform * maxOriginal;

	for (int i = 0; i < 3; i++)
	{
		normalsTransformed[i] = transform * normalsOriginal[i];
	}
}

void PieceView::setTransform(Matrix4 transform)
{
	this->transform = transform;
}

Vector4& PieceView::getMin(bool applyTransform)
{
	if (applyTransform)
	{
		this->applyTransform();
		return minTransformed;
	}
	else
	{
		return minOriginal;
	}
}

Vector4& PieceView::getMax(bool applyTransform)
{
	if (applyTransform)
	{
		this->applyTransform();
		return maxTransformed;
	}
	else
	{
		return maxOriginal;
	}
}

Vector4 (*PieceView::getNormals(bool applyTransform))[3]
{
	if (applyTransform)
	{
		this->applyTransform();
		return &normalsTransformed;
	}
	else
	{
		return &normalsOriginal;
	}
}
PieceView::Face PieceView::getIntersectionFace()
{
}

