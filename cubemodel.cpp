#include <iostream>
#include "cubemodel.h"

CubeModel::CubeModel()
{
	reset();
}

CubeModel::~CubeModel()
{
}

void CubeModel::reset(bool clear)
{
	if (clear)
	{
		pastMovesStack.clear();
		futureMovesStack.clear();
	}
	
	int id = 0;

	for (int z = 0; z < 3; z++)
	{
		for (int y = 0; y < 3; y++)
		{
			for (int x = 0; x < 3; x++)
			{
				cube[x][y][z].id = id++;

				switch (x) // values increase from left to right
				{
				case 0:
					// left face
					cube[x][y][z].face[4] = WHITE;
					// right face
					cube[x][y][z].face[5] = BLACK;
					break;
				case 1:
					cube[x][y][z].face[4] = BLACK;
					cube[x][y][z].face[5] = BLACK;
					break;
				case 2:
					cube[x][y][z].face[4] = BLACK;
					cube[x][y][z].face[5] = YELLOW;
					break;
				}

				switch (y) // values increase from bottom to top
				{
				case 0:
					// up face
					cube[x][y][z].face[2] = BLACK;
					// down face
					cube[x][y][z].face[3] = RED;
					break;
				case 1:
					cube[x][y][z].face[2] = BLACK;
					cube[x][y][z].face[3] = BLACK;
					break;
				case 2:
					cube[x][y][z].face[2] = ORANGE;
					cube[x][y][z].face[3] = BLACK;
					break;
				}

				switch (z) // values increase from back to front
				{
				case 0:
					// front face
					cube[x][y][z].face[0] = BLACK;
					// back face
					cube[x][y][z].face[1] = GREEN;
					break;
				case 1:
					cube[x][y][z].face[0] = BLACK;
					cube[x][y][z].face[1] = BLACK;
					break;
				case 2:
					cube[x][y][z].face[0] = BLUE;
					cube[x][y][z].face[1] = BLACK;
					break;
				}

			}
		}
	}
}

bool CubeModel::save(std::ofstream file)
{
	return false;
}

bool CubeModel::load(std::ifstream file)
{
	return false;
}

void CubeModel::turn(Turn type, bool cw)
{
	Piece temp;

	switch (type)
	{
	case FRONT:
		std::cout << "front ";
		if (cw)
		{
			std::cout << "cw\n";
			temp = cube[0][2][2];

			cube[0][2][2].id = cube[0][0][2].id;
			cube[0][2][2].face[UP] = cube[0][0][2].face[LEFT];
			cube[0][2][2].face[LEFT] = cube[0][0][2].face[DOWN];

			cube[0][0][2].id = cube[2][0][2].id;
			cube[0][0][2].face[LEFT] = cube[2][0][2].face[DOWN];
			cube[0][0][2].face[DOWN] = cube[2][0][2].face[RIGHT];

			cube[2][0][2].id = cube[2][2][2].id;
			cube[2][0][2].face[DOWN] = cube[2][2][2].face[RIGHT];
			cube[2][0][2].face[RIGHT] = cube[2][2][2].face[UP];

			cube[2][2][2].id = temp.id;
			cube[2][2][2].face[RIGHT] = temp.face[UP];
			cube[2][2][2].face[UP] = temp.face[LEFT];

			temp = cube[1][2][2];

			cube[1][2][2].id = cube[0][1][2].id;
			cube[1][2][2].face[UP] = cube[0][1][2].face[LEFT];

			cube[0][1][2].id = cube[1][0][2].id;
			cube[0][1][2].face[LEFT] = cube[1][0][2].face[DOWN];

			cube[1][0][2].id = cube[2][1][2].id;
			cube[1][0][2].face[DOWN] = cube[2][1][2].face[RIGHT];

			cube[2][1][2].id = temp.id;
			cube[2][1][2].face[RIGHT] = temp.face[UP];
		}
		else
		{
			std::cout << "ccw\n";
			temp = cube[0][2][2];

			cube[0][2][2].id = cube[2][2][2].id;
			cube[0][2][2].face[LEFT] = cube[2][2][2].face[UP];
			cube[0][2][2].face[UP] = cube[2][2][2].face[RIGHT];

			cube[2][2][2].id = cube[2][0][2].id;
			cube[2][2][2].face[UP] = cube[2][0][2].face[RIGHT];
			cube[2][2][2].face[RIGHT] = cube[2][0][2].face[DOWN];

			cube[2][0][2].id = cube[0][0][2].id;
			cube[2][0][2].face[RIGHT] = cube[0][0][2].face[DOWN];
			cube[2][0][2].face[DOWN] = cube[0][0][2].face[LEFT];

			cube[0][0][2].id = temp.id;
			cube[0][0][2].face[DOWN] = temp.face[LEFT];
			cube[0][0][2].face[LEFT] = temp.face[UP];

			temp = cube[1][2][2];

			cube[1][2][2].id = cube[2][1][2].id;
			cube[1][2][2].face[UP] = cube[2][1][2].face[RIGHT];

			cube[2][1][2].id = cube[1][0][2].id;
			cube[2][1][2].face[RIGHT] = cube[1][0][2].face[DOWN];

			cube[1][0][2].id = cube[0][1][2].id;
			cube[1][0][2].face[DOWN] = cube[0][1][2].face[LEFT];

			cube[0][1][2].id = temp.id;
			cube[0][1][2].face[LEFT] = temp.face[UP];
		}
		break;
	case BACK:
		std::cout << "back\n";
		if (cw)
		{
			std::cout << "cw\n";
			temp = cube[0][2][0];

			cube[0][2][0].id = cube[2][2][0].id;
			cube[0][2][0].face[LEFT] = cube[2][2][0].face[UP];
			cube[0][2][0].face[UP] = cube[2][2][0].face[RIGHT];

			cube[2][2][0].id = cube[2][0][0].id;
			cube[2][2][0].face[UP] = cube[2][0][0].face[RIGHT];
			cube[2][2][0].face[RIGHT] = cube[2][0][0].face[DOWN];

			cube[2][0][0].id = cube[0][0][0].id;
			cube[2][0][0].face[RIGHT] = cube[0][0][0].face[DOWN];
			cube[2][0][0].face[DOWN] = cube[0][0][0].face[LEFT];

			cube[0][0][0].id = temp.id;
			cube[0][0][0].face[DOWN] = temp.face[LEFT];
			cube[0][0][0].face[LEFT] = temp.face[UP];

			temp = cube[1][2][0];

			cube[1][2][0].id = cube[2][1][0].id;
			cube[1][2][0].face[UP] = cube[2][1][0].face[RIGHT];

			cube[2][1][0].id = cube[1][0][0].id;
			cube[2][1][0].face[RIGHT] = cube[1][0][0].face[DOWN];

			cube[1][0][0].id = cube[0][1][0].id;
			cube[1][0][0].face[DOWN] = cube[0][1][0].face[LEFT];

			cube[0][1][0].id = temp.id;
			cube[0][1][0].face[LEFT] = temp.face[UP];
		}
		else
		{
			std::cout << "ccw\n";
			temp = cube[0][2][0];

			cube[0][2][0].id = cube[0][0][0].id;
			cube[0][2][0].face[UP] = cube[0][0][0].face[LEFT];
			cube[0][2][0].face[LEFT] = cube[0][0][0].face[DOWN];

			cube[0][0][0].id = cube[2][0][0].id;
			cube[0][0][0].face[LEFT] = cube[2][0][0].face[DOWN];
			cube[0][0][0].face[DOWN] = cube[2][0][0].face[RIGHT];

			cube[2][0][0].id = cube[2][2][0].id;
			cube[2][0][0].face[DOWN] = cube[2][2][0].face[RIGHT];
			cube[2][0][0].face[RIGHT] = cube[2][2][0].face[UP];

			cube[2][2][0].id = temp.id;
			cube[2][2][0].face[RIGHT] = temp.face[UP];
			cube[2][2][0].face[UP] = temp.face[LEFT];

			temp = cube[1][2][0];

			cube[1][2][0].id = cube[0][1][0].id;
			cube[1][2][0].face[UP] = cube[0][1][0].face[LEFT];

			cube[0][1][0].id = cube[1][0][0].id;
			cube[0][1][0].face[LEFT] = cube[1][0][0].face[DOWN];

			cube[1][0][0].id = cube[2][1][0].id;
			cube[1][0][0].face[DOWN] = cube[2][1][0].face[RIGHT];

			cube[2][1][0].id = temp.id;
			cube[2][1][0].face[RIGHT] = temp.face[UP];
		}
		break;
	case UP:
		std::cout << "up ";
		if (cw)
		{
			std::cout << "cw\n";
			temp = cube[0][2][0];

			cube[0][2][0].id = cube[0][2][2].id;
			cube[0][2][0].face[BACK] = cube[0][2][2].face[LEFT];
			cube[0][2][0].face[LEFT] = cube[0][2][2].face[FRONT];

			cube[0][2][2].id = cube[2][2][2].id;
			cube[0][2][2].face[LEFT] = cube[2][2][2].face[FRONT];
			cube[0][2][2].face[FRONT] = cube[2][2][2].face[RIGHT];

			cube[2][2][2].id = cube[2][2][0].id;
			cube[2][2][2].face[FRONT] = cube[2][2][0].face[RIGHT];
			cube[2][2][2].face[RIGHT] = cube[2][2][0].face[BACK];

			cube[2][2][0].id = temp.id;
			cube[2][2][0].face[RIGHT] = temp.face[BACK];
			cube[2][2][0].face[BACK] = temp.face[LEFT];

			temp = cube[1][2][0];

			cube[1][2][0].id = cube[0][2][1].id;
			cube[1][2][0].face[BACK] = cube[0][2][1].face[LEFT];

			cube[0][2][1].id = cube[1][2][2].id;
			cube[0][2][1].face[LEFT] = cube[1][2][2].face[FRONT];

			cube[1][2][2].id = cube[2][2][1].id;
			cube[1][2][2].face[FRONT] = cube[2][2][1].face[RIGHT];

			cube[2][2][1].id = temp.id;
			cube[2][2][1].face[RIGHT] = temp.face[BACK];
		}
		else
		{
			std::cout << "ccw\n";
			temp = cube[0][2][0];

			cube[0][2][0].id = cube[2][2][0].id;
			cube[0][2][0].face[LEFT] = cube[2][2][0].face[BACK];
			cube[0][2][0].face[BACK] = cube[2][2][0].face[RIGHT];

			cube[2][2][0].id = cube[2][2][2].id;
			cube[2][2][0].face[BACK] = cube[2][2][2].face[RIGHT];
			cube[2][2][0].face[RIGHT] = cube[2][2][2].face[FRONT];

			cube[2][2][2].id = cube[0][2][2].id;
			cube[2][2][2].face[RIGHT] = cube[0][2][2].face[FRONT];
			cube[2][2][2].face[FRONT] = cube[0][2][2].face[LEFT];

			cube[0][2][2].id = temp.id;
			cube[0][2][2].face[FRONT] = temp.face[LEFT];
			cube[0][2][2].face[LEFT] = temp.face[BACK];

			temp = cube[1][2][0];

			cube[1][2][0].id = cube[2][2][1].id;
			cube[1][2][0].face[BACK] = cube[2][2][1].face[RIGHT];

			cube[2][2][1].id = cube[1][2][2].id;
			cube[2][2][1].face[RIGHT] = cube[1][2][2].face[FRONT];

			cube[1][2][2].id = cube[0][2][1].id;
			cube[1][2][2].face[FRONT] = cube[0][2][1].face[LEFT];

			cube[0][2][1].id = temp.id;
			cube[0][2][1].face[LEFT] = temp.face[BACK];
		}
		break;
	case DOWN:
		std::cout << "down ";
		if (cw)
		{
			std::cout << "cw\n";
			temp = cube[0][0][0];

			cube[0][0][0].id = cube[2][0][0].id;
			cube[0][0][0].face[LEFT] = cube[2][0][0].face[BACK];
			cube[0][0][0].face[BACK] = cube[2][0][0].face[RIGHT];

			cube[2][0][0].id = cube[2][0][2].id;
			cube[2][0][0].face[BACK] = cube[2][0][2].face[RIGHT];
			cube[2][0][0].face[RIGHT] = cube[2][0][2].face[FRONT];

			cube[2][0][2].id = cube[0][0][2].id;
			cube[2][0][2].face[RIGHT] = cube[0][0][2].face[FRONT];
			cube[2][0][2].face[FRONT] = cube[0][0][2].face[LEFT];

			cube[0][0][2].id = temp.id;
			cube[0][0][2].face[FRONT] = temp.face[LEFT];
			cube[0][0][2].face[LEFT] = temp.face[BACK];

			temp = cube[1][0][0];

			cube[1][0][0].id = cube[2][0][1].id;
			cube[1][0][0].face[BACK] = cube[2][0][1].face[RIGHT];

			cube[2][0][1].id = cube[1][0][2].id;
			cube[2][0][1].face[RIGHT] = cube[1][0][2].face[FRONT];

			cube[1][0][2].id = cube[0][0][1].id;
			cube[1][0][2].face[FRONT] = cube[0][0][1].face[LEFT];

			cube[0][0][1].id = temp.id;
			cube[0][0][1].face[LEFT] = temp.face[BACK];
		}
		else
		{
			std::cout << "ccw\n";
			temp = cube[0][0][0];

			cube[0][0][0].id = cube[0][0][2].id;
			cube[0][0][0].face[BACK] = cube[0][0][2].face[LEFT];
			cube[0][0][0].face[LEFT] = cube[0][0][2].face[FRONT];

			cube[0][0][2].id = cube[2][0][2].id;
			cube[0][0][2].face[LEFT] = cube[2][0][2].face[FRONT];
			cube[0][0][2].face[FRONT] = cube[2][0][2].face[RIGHT];

			cube[2][0][2].id = cube[2][0][0].id;
			cube[2][0][2].face[FRONT] = cube[2][0][0].face[RIGHT];
			cube[2][0][2].face[RIGHT] = cube[2][0][0].face[BACK];

			cube[2][0][0].id = temp.id;
			cube[2][0][0].face[RIGHT] = temp.face[BACK];
			cube[2][0][0].face[BACK] = temp.face[LEFT];

			temp = cube[1][0][0];

			cube[1][0][0].id = cube[0][0][1].id;
			cube[1][0][0].face[BACK] = cube[0][0][1].face[LEFT];

			cube[0][0][1].id = cube[1][0][2].id;
			cube[0][0][1].face[LEFT] = cube[1][0][2].face[FRONT];

			cube[1][0][2].id = cube[2][0][1].id;
			cube[1][0][2].face[FRONT] = cube[2][0][1].face[RIGHT];

			cube[2][0][1].id = temp.id;
			cube[2][0][1].face[RIGHT] = temp.face[BACK];
		}
		break;
	case LEFT:
		std::cout << "left ";
		if (cw)
		{
			std::cout << "cw\n";
			temp = cube[0][2][0];

			cube[0][2][0].id = cube[0][0][0].id;
			cube[0][2][0].face[UP] = cube[0][0][0].face[BACK];
			cube[0][2][0].face[BACK] = cube[0][0][0].face[DOWN];

			cube[0][0][0].id = cube[0][0][2].id;
			cube[0][0][0].face[BACK] = cube[0][0][2].face[DOWN];
			cube[0][0][0].face[DOWN] = cube[0][0][2].face[FRONT];

			cube[0][0][2].id = cube[0][2][2].id;
			cube[0][0][2].face[DOWN] = cube[0][2][2].face[FRONT];
			cube[0][0][2].face[FRONT] = cube[0][2][2].face[UP];

			cube[0][2][2].id = temp.id;
			cube[0][2][2].face[FRONT] = temp.face[UP];
			cube[0][2][2].face[UP] = temp.face[BACK];

			temp = cube[0][2][1];

			cube[0][2][1].id = cube[0][1][0].id;
			cube[0][2][1].face[UP] = cube[0][1][0].face[BACK];

			cube[0][1][0].id = cube[0][0][1].id;
			cube[0][1][0].face[BACK] = cube[0][0][1].face[DOWN];

			cube[0][0][1].id = cube[0][1][2].id;
			cube[0][0][1].face[DOWN] = cube[0][1][2].face[FRONT];

			cube[0][1][2].id = temp.id;
			cube[0][1][2].face[FRONT] = temp.face[UP];
		}
		else
		{
			std::cout << "ccw\n";
			temp = cube[0][2][0];

			cube[0][2][0].id = cube[0][2][2].id;
			cube[0][2][0].face[BACK] = cube[0][2][2].face[UP];
			cube[0][2][0].face[UP] = cube[0][2][2].face[FRONT];

			cube[0][2][2].id = cube[0][0][2].id;
			cube[0][2][2].face[UP] = cube[0][0][2].face[FRONT];
			cube[0][2][2].face[FRONT] = cube[0][0][2].face[DOWN];

			cube[0][0][2].id = cube[0][0][0].id;
			cube[0][0][2].face[FRONT] = cube[0][0][0].face[DOWN];
			cube[0][0][2].face[DOWN] = cube[0][0][0].face[BACK];

			cube[0][0][0].id = temp.id;
			cube[0][0][0].face[DOWN] = temp.face[BACK];
			cube[0][0][0].face[BACK] = temp.face[UP];

			temp = cube[0][2][1];

			cube[0][2][1].id = cube[0][1][2].id;
			cube[0][2][1].face[UP] = cube[0][1][2].face[FRONT];

			cube[0][1][2].id = cube[0][0][1].id;
			cube[0][1][2].face[FRONT] = cube[0][0][1].face[DOWN];

			cube[0][0][1].id = cube[0][1][0].id;
			cube[0][0][1].face[DOWN] = cube[0][1][0].face[BACK];

			cube[0][1][0].id = temp.id;
			cube[0][1][0].face[BACK] = temp.face[UP];
		}
		break;
	case RIGHT:
		std::cout << "right ";
		if (cw)
		{
			std::cout << "cw\n";
			temp = cube[2][2][0];

			cube[2][2][0].id = cube[2][2][2].id;
			cube[2][2][0].face[BACK] = cube[2][2][2].face[UP];
			cube[2][2][0].face[UP] = cube[2][2][2].face[FRONT];

			cube[2][2][2].id = cube[2][0][2].id;
			cube[2][2][2].face[UP] = cube[2][0][2].face[FRONT];
			cube[2][2][2].face[FRONT] = cube[2][0][2].face[DOWN];

			cube[2][0][2].id = cube[2][0][0].id;
			cube[2][0][2].face[FRONT] = cube[2][0][0].face[DOWN];
			cube[2][0][2].face[DOWN] = cube[2][0][0].face[BACK];

			cube[2][0][0].id = temp.id;
			cube[2][0][0].face[DOWN] = temp.face[BACK];
			cube[2][0][0].face[BACK] = temp.face[UP];

			temp = cube[2][2][1];

			cube[2][2][1].id = cube[2][1][2].id;
			cube[2][2][1].face[UP] = cube[2][1][2].face[FRONT];

			cube[2][1][2].id = cube[2][0][1].id;
			cube[2][1][2].face[FRONT] = cube[2][0][1].face[DOWN];

			cube[2][0][1].id = cube[2][1][0].id;
			cube[2][0][1].face[DOWN] = cube[2][1][0].face[BACK];

			cube[2][1][0].id = temp.id;
			cube[2][1][0].face[BACK] = temp.face[UP];
		}
		else
		{
			std::cout << "ccw\n";
			temp = cube[2][2][0];

			cube[2][2][0].id = cube[2][0][0].id;
			cube[2][2][0].face[UP] = cube[2][0][0].face[BACK];
			cube[2][2][0].face[BACK] = cube[2][0][0].face[DOWN];

			cube[2][0][0].id = cube[2][0][2].id;
			cube[2][0][0].face[BACK] = cube[2][0][2].face[DOWN];
			cube[2][0][0].face[DOWN] = cube[2][0][2].face[FRONT];

			cube[2][0][2].id = cube[2][2][2].id;
			cube[2][0][2].face[DOWN] = cube[2][2][2].face[FRONT];
			cube[2][0][2].face[FRONT] = cube[2][2][2].face[UP];

			cube[2][2][2].id = temp.id;
			cube[2][2][2].face[FRONT] = temp.face[UP];
			cube[2][2][2].face[UP] = temp.face[BACK];

			temp = cube[2][2][1];

			cube[2][2][1].id = cube[2][1][0].id;
			cube[2][2][1].face[UP] = cube[2][1][0].face[BACK];

			cube[2][1][0].id = cube[2][0][1].id;
			cube[2][1][0].face[BACK] = cube[2][0][1].face[DOWN];

			cube[2][0][1].id = cube[2][1][2].id;
			cube[2][0][1].face[DOWN] = cube[2][1][2].face[FRONT];

			cube[2][1][2].id = temp.id;
			cube[2][1][2].face[FRONT] = temp.face[UP];
		}
		break;
	case X_AXIS:
		std::cout << "x-axis ";
		if (cw)
		{
			std::cout << "cw\n";
			turn(LEFT, false);
			turn(RIGHT, true);

			temp = cube[1][2][2];

			cube[1][2][2].id = cube[1][0][2].id;
			cube[1][2][2].face[UP] = cube[1][0][2].face[FRONT];
			cube[1][2][2].face[FRONT] = cube[1][0][2].face[DOWN];

			cube[1][0][2].id = cube[1][0][0].id;
			cube[1][0][2].face[FRONT] = cube[1][0][0].face[DOWN];
			cube[1][0][2].face[DOWN] = cube[1][0][0].face[BACK];

			cube[1][0][0].id = cube[1][2][0].id;
			cube[1][0][0].face[DOWN] = cube[1][2][0].face[BACK];
			cube[1][0][0].face[BACK] = cube[1][2][0].face[UP];

			cube[1][2][0].id = temp.id;
			cube[1][2][0].face[BACK] = temp.face[UP];
			cube[1][2][0].face[UP] = temp.face[FRONT];

			temp = cube[1][2][1];

			cube[1][2][1].id = cube[1][1][2].id;
			cube[1][2][1].face[UP] = cube[1][1][2].face[FRONT];

			cube[1][1][2].id = cube[1][0][1].id;
			cube[1][1][2].face[FRONT] = cube[1][0][1].face[DOWN];

			cube[1][0][1].id = cube[1][1][0].id;
			cube[1][0][1].face[DOWN] = cube[1][1][0].face[BACK];

			cube[1][1][0].id = temp.id;
			cube[1][1][0].face[BACK] = temp.face[UP];
		}
		else
		{
			std::cout << "ccw\n";
			turn(LEFT, true);
			turn(RIGHT, false);

			temp = cube[1][2][2];

			cube[1][2][2].id = cube[1][2][0].id;
			cube[1][2][2].face[FRONT] = cube[1][2][0].face[UP];
			cube[1][2][2].face[UP] = cube[1][2][0].face[BACK];

			cube[1][2][0].id = cube[1][0][0].id;
			cube[1][2][0].face[UP] = cube[1][0][0].face[BACK];
			cube[1][2][0].face[BACK] = cube[1][0][0].face[DOWN];

			cube[1][0][0].id = cube[1][0][2].id;
			cube[1][0][0].face[BACK] = cube[1][0][2].face[DOWN];
			cube[1][0][0].face[DOWN] = cube[1][0][2].face[FRONT];

			cube[1][0][2].id = temp.id;
			cube[1][0][2].face[DOWN] = temp.face[FRONT];
			cube[1][0][2].face[FRONT] = temp.face[UP];

			temp = cube[1][2][1];

			cube[1][2][1].id = cube[1][1][0].id;
			cube[1][2][1].face[UP] = cube[1][1][0].face[BACK];

			cube[1][1][0].id = cube[1][0][1].id;
			cube[1][1][0].face[BACK] = cube[1][0][1].face[DOWN];

			cube[1][0][1].id = cube[1][1][2].id;
			cube[1][0][1].face[DOWN] = cube[1][1][2].face[FRONT];

			cube[1][1][2].id = temp.id;
			cube[1][1][2].face[FRONT] = temp.face[UP];
		}
		break;
	case Y_AXIS:
		std::cout << "y-axis ";
		if (cw)
		{
			std::cout << "cw\n";
			turn(UP, true);
			turn(DOWN, false);

			temp = cube[0][1][0];

			cube[0][1][0].id = cube[0][1][2].id;
			cube[0][1][0].face[BACK] = cube[0][1][2].face[LEFT];
			cube[0][1][0].face[LEFT] = cube[0][1][2].face[FRONT];

			cube[0][1][2].id = cube[2][1][2].id;
			cube[0][1][2].face[LEFT] = cube[2][1][2].face[FRONT];
			cube[0][1][2].face[FRONT] = cube[2][1][2].face[RIGHT];

			cube[2][1][2].id = cube[2][1][0].id;
			cube[2][1][2].face[FRONT] = cube[2][1][0].face[RIGHT];
			cube[2][1][2].face[RIGHT] = cube[2][1][0].face[BACK];

			cube[2][1][0].id = temp.id;
			cube[2][1][0].face[RIGHT] = temp.face[BACK];
			cube[2][1][0].face[BACK] = temp.face[LEFT];

			temp = cube[1][1][0];

			cube[1][1][0].id = cube[0][1][1].id;
			cube[1][1][0].face[BACK] = cube[0][1][1].face[LEFT];

			cube[0][1][1].id = cube[1][1][2].id;
			cube[0][1][1].face[LEFT] = cube[1][1][2].face[FRONT];

			cube[1][1][2].id = cube[2][1][1].id;
			cube[1][1][2].face[FRONT] = cube[2][1][1].face[RIGHT];

			cube[2][1][1].id = temp.id;
			cube[2][1][1].face[RIGHT] = temp.face[BACK];
		}
		else
		{
			std::cout << "ccw\n";
			turn(UP, false);
			turn(DOWN, true);

			temp = cube[0][1][0];

			cube[0][1][0].id = cube[2][1][0].id;
			cube[0][1][0].face[LEFT] = cube[2][1][0].face[BACK];
			cube[0][1][0].face[BACK] = cube[2][1][0].face[RIGHT];

			cube[2][1][0].id = cube[2][1][2].id;
			cube[2][1][0].face[BACK] = cube[2][1][2].face[RIGHT];
			cube[2][1][0].face[RIGHT] = cube[2][1][2].face[FRONT];

			cube[2][1][2].id = cube[0][1][2].id;
			cube[2][1][2].face[RIGHT] = cube[0][1][2].face[FRONT];
			cube[2][1][2].face[FRONT] = cube[0][1][2].face[LEFT];

			cube[0][1][2].id = temp.id;
			cube[0][1][2].face[FRONT] = temp.face[LEFT];
			cube[0][1][2].face[LEFT] = temp.face[BACK];

			temp = cube[1][1][0];

			cube[1][1][0].id = cube[2][1][1].id;
			cube[1][1][0].face[BACK] = cube[2][1][1].face[RIGHT];

			cube[2][1][1].id = cube[1][1][2].id;
			cube[2][1][1].face[RIGHT] = cube[1][1][2].face[FRONT];

			cube[1][1][2].id = cube[0][1][1].id;
			cube[1][1][2].face[FRONT] = cube[0][1][1].face[LEFT];

			cube[0][1][1].id = temp.id;
			cube[0][1][1].face[LEFT] = temp.face[BACK];
		}
		break;
	case Z_AXIS:
		std::cout << "z-axis ";
		if (cw)
		{
			std::cout << "cw\n";
			turn(FRONT, true);
			turn(BACK, false);

			temp = cube[0][2][1];

			cube[0][2][1].id = cube[0][0][1].id;
			cube[0][2][1].face[UP] = cube[0][0][1].face[LEFT];
			cube[0][2][1].face[LEFT] = cube[0][0][1].face[DOWN];

			cube[0][0][1].id = cube[2][0][1].id;
			cube[0][0][1].face[LEFT] = cube[2][0][1].face[DOWN];
			cube[0][0][1].face[DOWN] = cube[2][0][1].face[RIGHT];

			cube[2][0][1].id = cube[2][2][1].id;
			cube[2][0][1].face[DOWN] = cube[2][2][1].face[RIGHT];
			cube[2][0][1].face[RIGHT] = cube[2][2][1].face[UP];

			cube[2][2][1].id = temp.id;
			cube[2][2][1].face[RIGHT] = temp.face[UP];
			cube[2][2][1].face[UP] = temp.face[LEFT];

			temp = cube[1][2][1];

			cube[1][2][1].id = cube[0][1][1].id;
			cube[1][2][1].face[UP] = cube[0][1][1].face[LEFT];

			cube[0][1][1].id = cube[1][0][1].id;
			cube[0][1][1].face[LEFT] = cube[1][0][1].face[DOWN];

			cube[1][0][1].id = cube[2][1][1].id;
			cube[1][0][1].face[DOWN] = cube[2][1][1].face[RIGHT];

			cube[2][1][1].id = temp.id;
			cube[2][1][1].face[RIGHT] = temp.face[UP];
		}
		else
		{
			std::cout << "ccw\n";
			turn(FRONT, false);
			turn(BACK, true);

			temp = cube[0][2][1];

			cube[0][2][1].id = cube[2][2][1].id;
			cube[0][2][1].face[LEFT] = cube[2][2][1].face[UP];
			cube[0][2][1].face[UP] = cube[2][2][1].face[RIGHT];

			cube[2][2][1].id = cube[2][0][1].id;
			cube[2][2][1].face[UP] = cube[2][0][1].face[RIGHT];
			cube[2][2][1].face[RIGHT] = cube[2][0][1].face[DOWN];

			cube[2][0][1].id = cube[0][0][1].id;
			cube[2][0][1].face[RIGHT] = cube[0][0][1].face[DOWN];
			cube[2][0][1].face[DOWN] = cube[0][0][1].face[LEFT];

			cube[0][0][1].id = temp.id;
			cube[0][0][1].face[DOWN] = temp.face[LEFT];
			cube[0][0][1].face[LEFT] = temp.face[UP];

			temp = cube[1][2][1];

			cube[1][2][1].id = cube[2][1][1].id;
			cube[1][2][1].face[UP] = cube[2][1][1].face[RIGHT];

			cube[2][1][1].id = cube[1][0][1].id;
			cube[2][1][1].face[RIGHT] = cube[1][0][1].face[DOWN];

			cube[1][0][1].id = cube[0][1][1].id;
			cube[1][0][1].face[DOWN] = cube[0][1][1].face[LEFT];

			cube[0][1][1].id = temp.id;
			cube[0][1][1].face[LEFT] = temp.face[UP];
		}
		break;
	}
}

void CubeModel::turn(Move move)
{
	turn(move.type, move.cw);
}

bool CubeModel::checkForTarget(Color target[6][9])
{
	return false;
}

int CubeModel::solveForTarget(int maxDepth, Color target[6][9])
{
	return 0;
}

CubeModel::Piece& CubeModel::getPiece(int x, int y, int z)
{
	return cube[x + 1][y + 1][z + 1];
}

/*CubeModel::MoveIterator CubeModel::getMoveIterator(int numMoves)
{
	// TODO: minimize stack operations
	while (!futureMovesStack.empty())
	{
		turn(futureMovesStack.back());
		pastMovesStack.push_back(futureMovesStack.back());
		futureMovesStack.pop_back();
	}

	if (numMoves == 0)
	{
		pastMovesStack.swap(futureMovesStack);
		reset(false);
	}
	else
	{
		for (int i = 0; i < numMoves; i++)
		{
			turn(pastMovesStack.back().type, !(pastMovesStack.back().cw));
			futureMovesStack.push_back(pastMovesStack.back());
			pastMovesStack.pop_back();
		}
	}
}

bool CubeModel::MoveIterator::hasNext()
{
	return !futureMovesStack.empty();
}

CubeModel::Move& CubeModel::MoveIterator::next()
{
	turn(futureMovesStack.back());
	pastMovesStack.push_back(futureMovesStack.back());
	futureMovesStack.pop_back();

	return pastMovesStack.back();
}//*/
