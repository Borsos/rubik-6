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

void CubeModel::turn_piece(Turn type, Piece& source, Piece& destination, bool cw)
{
	switch (type)
	{
	case X_AXIS:
		destination.id = source.id;
		destination.face[LEFT] = source.face[LEFT];
		destination.face[RIGHT] = source.face[RIGHT];

		if (cw)
		{
			destination.face[FRONT] = source.face[DOWN];
			destination.face[DOWN] = source.face[BACK];
			destination.face[BACK] = source.face[UP];
			destination.face[UP] = source.face[FRONT];
		}
		else
		{
			destination.face[FRONT] = source.face[UP];
			destination.face[UP] = source.face[BACK];
			destination.face[BACK] = source.face[DOWN];
			destination.face[DOWN] = source.face[FRONT];
		}
		break;
	case Y_AXIS:
		destination.id = source.id;
		destination.face[DOWN] = source.face[DOWN];
		destination.face[UP] = source.face[UP];

		if (cw)
		{
			destination.face[LEFT] = source.face[FRONT];
			destination.face[FRONT] = source.face[RIGHT];
			destination.face[RIGHT] = source.face[BACK];
			destination.face[BACK] = source.face[LEFT];
		}
		else
		{
			destination.face[LEFT] = source.face[BACK];
			destination.face[BACK] = source.face[RIGHT];
			destination.face[RIGHT] = source.face[FRONT];
			destination.face[FRONT] = source.face[LEFT];
		}
		break;
	case Z_AXIS:
		destination.id = source.id;
		destination.face[BACK] = source.face[BACK];
		destination.face[FRONT] = source.face[FRONT];

		if (cw)
		{
			destination.face[LEFT] = source.face[DOWN];
			destination.face[DOWN] = source.face[RIGHT];
			destination.face[RIGHT] = source.face[UP];
			destination.face[UP] = source.face[LEFT];
		}
		else
		{
			destination.face[LEFT] = source.face[UP];
			destination.face[UP] = source.face[RIGHT];
			destination.face[RIGHT] = source.face[DOWN];
			destination.face[DOWN] = source.face[LEFT];
		}
		break;
	default:
		std::cerr << "ERROR: Illegal type specified for turn_piece.\n";
	}
}

void CubeModel::turn_layer(Turn type, int layer, bool cw)
{
	Piece temp_corner;
	Piece temp_edge;

	int x_corner, y_corner, z_corner;
	int x_edge, y_edge, z_edge;
	int x_source, y_source, z_source;

	switch (type)
	{
	case X_AXIS:
		y_corner = 0;
		z_corner = 0;
		y_edge = 1;
		z_edge = 0;
		temp_corner = cube[layer][y_corner][z_corner];
		temp_edge = cube[layer][y_edge][z_edge];

		for (int i = 1; i < 4; i++)
		{
			if (cw)
			{
				y_source = 2 - z_corner;
				z_source = y_corner;
				turn_piece(X_AXIS, cube[layer][y_source][z_source], cube[layer][y_corner][z_corner], cw);
				y_corner = y_source;
				z_corner = z_source;

				y_source = 2 - z_edge;
				z_source = y_edge;
				turn_piece(X_AXIS, cube[layer][y_source][z_source], cube[layer][y_edge][z_edge], cw);
				y_edge = y_source;
				z_edge = z_source;
			}
			else
			{
				y_source = z_corner;
				z_source = 2 - y_corner;
				turn_piece(X_AXIS, cube[layer][y_source][z_source], cube[layer][y_corner][z_corner], cw);
				y_corner = y_source;
				z_corner = z_source;

				y_source = z_edge;
				z_source = 2 - y_edge;
				turn_piece(X_AXIS, cube[layer][y_source][z_source], cube[layer][y_edge][z_edge], cw);
				y_edge = y_source;
				z_edge = z_source;
			}
		}
		turn_piece(X_AXIS, temp_corner, cube[layer][y_corner][z_corner], cw);
		turn_piece(X_AXIS, temp_edge, cube[layer][y_edge][z_edge], cw);
		break;
	case Y_AXIS:
		x_corner = 0;
		z_corner = 0;
		x_edge = 1;
		z_edge = 0;
		temp_corner = cube[x_corner][layer][z_corner];
		temp_edge = cube[x_edge][layer][z_edge];

		for (int i = 1; i < 4; i++)
		{
			if (cw)
			{
				x_source = z_corner;
				z_source = 2 - x_corner;
				turn_piece(Y_AXIS, cube[x_source][layer][z_source], cube[x_corner][layer][z_corner], cw);
				x_corner = x_source;
				z_corner = z_source;

				x_source = z_edge;
				z_source = 2 - x_edge;
				turn_piece(Y_AXIS, cube[x_source][layer][z_source], cube[x_edge][layer][z_edge], cw);
				x_edge = x_source;
				z_edge = z_source;
			}
			else
			{
				x_source = 2 - z_corner;
				z_source = x_corner;
				turn_piece(Y_AXIS, cube[x_source][layer][z_source], cube[x_corner][layer][z_corner], cw);
				x_corner = x_source;
				z_corner = z_source;

				x_source = 2 - z_edge;
				z_source = x_edge;
				turn_piece(Y_AXIS, cube[x_source][layer][z_source], cube[x_edge][layer][z_edge], cw);
				x_edge = x_source;
				z_edge = z_source;
			}
		}
		turn_piece(Y_AXIS, temp_corner, cube[x_corner][layer][z_corner], cw);
		turn_piece(Y_AXIS, temp_edge, cube[x_edge][layer][z_edge], cw);
		break;
	case Z_AXIS:
		x_corner = 0;
		y_corner = 0;
		x_edge = 0;
		y_edge = 1;
		temp_corner = cube[x_corner][y_corner][layer];
		temp_edge = cube[x_edge][y_edge][layer];

		for (int i = 1; i < 4; i++)
		{
			if (cw)
			{
				x_source = 2 - y_corner;
				y_source = x_corner;
				turn_piece(Z_AXIS, cube[x_source][y_source][layer], cube[x_corner][y_corner][layer], cw);
				x_corner = x_source;
				y_corner = y_source;

				x_source = 2 - y_edge;
				y_source = x_edge;
				turn_piece(Z_AXIS, cube[x_source][y_source][layer], cube[x_edge][y_edge][layer], cw);
				x_edge = x_source;
				y_edge = y_source;
			}
			else
			{
				x_source = y_corner;
				y_source = 2 - x_corner;
				turn_piece(Z_AXIS, cube[x_source][y_source][layer], cube[x_corner][y_corner][layer], cw);
				x_corner = x_source;
				y_corner = y_source;

				x_source = y_edge;
				y_source = 2 - x_edge;
				turn_piece(Z_AXIS, cube[x_source][y_source][layer], cube[x_edge][y_edge][layer], cw);
				x_edge = x_source;
				y_edge = y_source;
			}
		}
		turn_piece(Z_AXIS, temp_corner, cube[x_corner][y_corner][layer], cw);
		turn_piece(Z_AXIS, temp_edge, cube[x_edge][y_edge][layer], cw);
		break;
	default:
		std::cerr << "ERROR: Illegal type specified for turn_layer.\n";
	}
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
			turn_layer(Z_AXIS, 2, true);
		}
		else
		{
			std::cout << "ccw\n";
			turn_layer(Z_AXIS, 2, false);
		}
		break;
	case BACK:
		std::cout << "back ";
		if (cw)
		{
			std::cout << "cw\n";
			// passing false to normalize direction of rotation
			turn_layer(Z_AXIS, 0, false);
		}
		else
		{
			std::cout << "ccw\n";
			// passing true to normalize direction of rotation
			turn_layer(Z_AXIS, 0, true);
		}
		break;
	case UP:
		std::cout << "up ";
		if (cw)
		{
			std::cout << "cw\n";
			turn_layer(Y_AXIS, 2, true);
		}
		else
		{
			std::cout << "ccw\n";
			turn_layer(Y_AXIS, 2, false);
		}
		break;
	case DOWN:
		std::cout << "down ";
		if (cw)
		{
			std::cout << "cw\n";
			// passing false to normalize direction of rotation
			turn_layer(Y_AXIS, 0, false);
		}
		else
		{
			std::cout << "ccw\n";
			// passing true to normalize direction of rotation
			turn_layer(Y_AXIS, 0, true);
		}
		break;
	case LEFT:
		std::cout << "left ";
		if (cw)
		{
			std::cout << "cw\n";
			// passing false to normalize direction of rotation
			turn_layer(X_AXIS, 0, false);
		}
		else
		{
			std::cout << "ccw\n";
			// passing true to normalize direction of rotation
			turn_layer(X_AXIS, 0, true);
		}
		break;
	case RIGHT:
		std::cout << "right ";
		if (cw)
		{
			std::cout << "cw\n";
			turn_layer(X_AXIS, 2, true);
		}
		else
		{
			std::cout << "ccw\n";
			turn_layer(X_AXIS, 2, false);
		}
		break;
	case X_AXIS:
		std::cout << "x-axis ";
		if (cw)
		{
			std::cout << "cw\n";
			turn_layer(X_AXIS, 0, true);
			turn_layer(X_AXIS, 1, true);
			turn_layer(X_AXIS, 2, true);
		}
		else
		{
			std::cout << "ccw\n";
			turn_layer(X_AXIS, 0, false);
			turn_layer(X_AXIS, 1, false);
			turn_layer(X_AXIS, 2, false);
		}
		break;
	case Y_AXIS:
		std::cout << "y-axis ";
		if (cw)
		{
			std::cout << "cw\n";
			turn_layer(Y_AXIS, 0, true);
			turn_layer(Y_AXIS, 1, true);
			turn_layer(Y_AXIS, 2, true);
		}
		else
		{
			std::cout << "ccw\n";
			turn_layer(Y_AXIS, 0, false);
			turn_layer(Y_AXIS, 1, false);
			turn_layer(Y_AXIS, 2, false);
		}
		break;
	case Z_AXIS:
		std::cout << "z-axis ";
		if (cw)
		{
			std::cout << "cw\n";
			turn_layer(Z_AXIS, 0, true);
			turn_layer(Z_AXIS, 1, true);
			turn_layer(Z_AXIS, 2, true);
		}
		else
		{
			std::cout << "ccw\n";
			turn_layer(Z_AXIS, 0, false);
			turn_layer(Z_AXIS, 1, false);
			turn_layer(Z_AXIS, 2, false);
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
