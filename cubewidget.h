#ifndef CUBEWIDGET_H
#define CUBEWIDGET_H

#include <QtOpenGL>
#include "cubemodel.h"

class CubeWidget : public QGLWidget
{
	Q_OBJECT

	private:
		CubeModel model;

		const float CUBE_SPACING;
		const float ROTATION_TIME;
		const int FRAMES_PER_SECOND;

		int animationTimer;

		bool isRotating;
		CubeModel::Move rotation;
		float rotationAngle;

		void setColor(CubeModel::Color color);
		void renderPiece(CubeModel::Piece& piece);
		void renderCube();

	public:
		CubeWidget(QWidget* parent);
	
	protected:
		void initializeGL();
		void resizeGL(int w, int h);
		void paintGL();

		void timerEvent(QTimerEvent* event);
		void mousePressEvent(QMouseEvent* event);


};

#endif //CUBEWIDGET_H
