#include <iostream>
#include "cubewidget.h"

CubeWidget::CubeWidget(QWidget* parent): QGLWidget(parent), CUBE_SPACING(2.2f), ROTATION_TIME(3.0f), FRAMES_PER_SECOND(40)
{
}

void CubeWidget::setColor(CubeModel::Color color)
{
	switch(color)
	{
	case CubeModel::BLACK:
		glColor3f(0.0f, 0.0f, 0.0f);
		break;
	case CubeModel::BLUE:
		glColor3f(0.0f, 0.0f, 0.5f);
		break;
	case CubeModel::GREEN:
		glColor3f(0.0f, 0.5f, 0.0f);
		break;
	case CubeModel::ORANGE:
		glColor3f(1.0f, 0.5f, 0.0f);
		break;
	case CubeModel::RED:
		glColor3f(0.5f, 0.0f, 0.0f);
		break;
	case CubeModel::WHITE:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	case CubeModel::YELLOW:
		glColor3f(1.0f, 1.0f, 0.0f);
		break;
	}
}

void CubeWidget::renderPiece(int x, int y, int z)
{
	/*for (int i = 0; i < 6; i++)
	{
		std::cout << piece.face[i] << " ";
	}
	std::cout << std::endl;//*/
	CubeModel::Piece pieceModel = model.getPiece(x, y, z);
	PieceView pieceView = pieceViews[x][y][z];

	Vector4 min = pieceView.getMin(false);
	Vector4 max = pieceView.getMax(false);
	Vector4 (*normals)[3] = pieceView.getNormals(false);

	glBegin(GL_QUADS);

	// front 
	setColor(pieceModel.face[0]);
	glNormal3fv((*normals[0]).getValues());
	glVertex3f(min[0], min[1], max[2]);
	glVertex3f(max[0], min[1], max[2]);
	glVertex3f(max[0], max[1], max[2]);
	glVertex3f(min[0], max[1], max[2]);

	// back
	setColor(pieceModel.face[1]);
	glNormal3fv((-(*normals[0])).getValues());
	glVertex3f(min[0], min[1], min[2]);
	glVertex3f(max[0], min[1], min[2]);
	glVertex3f(max[0], max[1], min[2]);
	glVertex3f(min[0], max[1], min[2]);

	// up
	setColor(pieceModel.face[2]);
	glNormal3fv((*normals[1]).getValues());
	glVertex3f(min[0], max[1], min[2]);
	glVertex3f(max[0], max[1], min[2]);
	glVertex3f(max[0], max[1], max[2]);
	glVertex3f(min[0], max[1], max[2]);

	// down
	setColor(pieceModel.face[3]);
	glNormal3fv((-(*normals[1])).getValues());
	glVertex3f(min[0], min[1], min[2]);
	glVertex3f(max[0], min[1], min[2]);
	glVertex3f(max[0], min[1], max[2]);
	glVertex3f(min[0], min[1], max[2]);

	// left
	setColor(pieceModel.face[4]);
	glNormal3fv((-(*normals[2])).getValues());
	glVertex3f(min[0], min[1], min[2]);
	glVertex3f(min[0], min[1], max[2]);
	glVertex3f(min[0], max[1], max[2]);
	glVertex3f(min[0], max[1], min[2]);

	// right
	setColor(pieceModel.face[5]);
	glNormal3fv((*normals[2]).getValues());
	glVertex3f(max[0], min[1], min[2]);
	glVertex3f(max[0], min[1], max[2]);
	glVertex3f(max[0], max[1], max[2]);
	glVertex3f(max[0], max[1], min[2]);

	glEnd();
}

void CubeWidget::renderCube()
{
	for (int x = -1; x < 2; x++)
	{
		for (int y = -1; y < 2; y++)
		{
			for (int z = -1; z < 2; z++)
			{
				glPushMatrix();

				if (isRotating)
				{
					switch (rotation.type)
					{
						case CubeModel::FRONT:
							if (z == 1)
							{
								if (rotation.cw)
								{
									glRotatef(360.0f - rotationAngle, 0.0f, 0.0f, 1.0f);
								}
								else
								{
									glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
								}
							}
							break;
						case CubeModel::BACK:
							if (z == -1)
							{
								if (rotation.cw)
								{
									glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
								}
								else
								{
									glRotatef(360.0f - rotationAngle, 0.0f, 0.0f, 1.0f);
								}
							}
							break;
						case CubeModel::UP:
							if (y == 1)
							{
								if (rotation.cw)
								{
									glRotatef(360.0f - rotationAngle, 0.0f, 1.0f, 0.0f);
								}
								else
								{
									glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
								}
							}
							break;
						case CubeModel::DOWN:
							if (y == -1)
							{
								if (rotation.cw)
								{
									glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
								}
								else
								{
									glRotatef(360.0f - rotationAngle, 0.0f, 1.0f, 0.0f);
								}
							}
							break;
						case CubeModel::LEFT:
							if (x == -1)
							{
								if (rotation.cw)
								{
									glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
								}
								else
								{
									glRotatef(360.0f - rotationAngle, 1.0f, 0.0f, 0.0f);
								}
							}
							break;
						case CubeModel::RIGHT:
							if (x == 1)
							{
								if (rotation.cw)
								{
									glRotatef(360.0f - rotationAngle, 1.0f, 0.0f, 0.0f);
								}
								else
								{
									glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
								}
							}
							break;
						default:
							break;
					}
				}

				glTranslatef(x * CUBE_SPACING, y * CUBE_SPACING, z * CUBE_SPACING);
				
				renderPiece(x, y, z);

				glPopMatrix();
			}
		}
	}
}

void CubeWidget::initializeGL()
{
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	animationTimer = startTimer(1000 / FRAMES_PER_SECOND);

	isRotating = true;
	rotation.type = CubeModel::Z_AXIS;
	//rotation.cw = false;
	rotation.cw = true;
	rotationAngle = 0.0f;
}

void CubeWidget::resizeGL(int w, int h)
{
	glViewport(0, 0, (GLint)w, (GLint)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)w/(GLfloat)h, 0.1f, 100.f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void CubeWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glTranslatef(0.0f, 0.0f, -16.0f);

	glBegin(GL_LINES);
	// global rotation axix
	glColor3f(1.0f, 1.0f, 1.0f); // white
	glVertex3f(0.0f, 0.0f, 0.0f);
	glVertex3f(10.0f, -10.0f, 0.0f);
	glEnd();

	glRotatef(40.0f, 1.0f, -1.0f, 0.0f);

	if (isRotating)
	{
		switch (rotation.type)
		{
		case CubeModel::X_AXIS:
			if (rotation.cw)
			{
				glRotatef(360.0f - rotationAngle, 1.0f, 0.0f, 0.0f);
			}
			else
			{
				glRotatef(rotationAngle, 1.0f, 0.0f, 0.0f);
			}
			break;
		case CubeModel::Y_AXIS:
			if (rotation.cw)
			{
				glRotatef(360.0f - rotationAngle, 0.0f, 1.0f, 0.0f);
			}
			else
			{
				glRotatef(rotationAngle, 0.0f, 1.0f, 0.0f);
			}
			break;
		case CubeModel::Z_AXIS:
			if (rotation.cw)
			{
				glRotatef(360.0f - rotationAngle, 0.0f, 0.0f, 1.0f);
			}
			else
			{
				glRotatef(rotationAngle, 0.0f, 0.0f, 1.0f);
			}
			break;
		default:
			break;
		}
	}

	renderCube();

	glBegin(GL_LINES);
	// picking ray
	glColor3f(1.0f, 0.0f, 1.0f); // pink
	glVertex3d(x_near, y_near, z_near);
	glVertex3d(x_far, y_far, z_far);
	glEnd();
}

void CubeWidget::timerEvent(QTimerEvent* event)
{
	if (isRotating)
	{
		rotationAngle += 90.0f / (ROTATION_TIME * FRAMES_PER_SECOND);
		if(rotationAngle > 90.0f)
		{
			//killTimer(animationTimer);
			//isRotating = false;
			model.turn(rotation);
			rotationAngle = 0.0f;

			rotation.type = (CubeModel::Turn) (rand() % 9);
			//rotation.type = CubeModel::Z_AXIS;
			rotation.cw = (bool) (rand() % 2);
			//rotation.cw = true;
		}
	}
	
	updateGL();
}


void CubeWidget::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		std::cout << "left click @ " << event->x() << ", " << event->y() << std::endl;

		GLint viewport[4];
		GLdouble mv_matrix[16], p_matrix[16];
		GLint y_converted;
		GLdouble wx, wy, wz;

		glGetIntegerv(GL_VIEWPORT, viewport);
		glGetDoublev(GL_MODELVIEW_MATRIX, mv_matrix);
		glGetDoublev(GL_PROJECTION_MATRIX, p_matrix);

		y_converted = viewport[3] - (GLint) event->y() - 1;
		std::cout << "converted coordinates: " << event->x() << ", " << y_converted << std::endl;

		gluUnProject((GLdouble) event->x(), (GLdouble) y_converted, 0.0, mv_matrix, p_matrix, viewport, &x_near, &y_near, &z_near);
		std::cout << "world coordinates @ near: " << x_near << ", " << y_near << ", " << z_near << std::endl;
		gluUnProject((GLdouble) event->x(), (GLdouble) y_converted, 1.0, mv_matrix, p_matrix, viewport, &x_far, &y_far, &z_far);
		std::cout << "world coordinates @ far: " << x_far << ", " << y_far << ", " << z_far << std::endl;

		updateGL();
	}
}

