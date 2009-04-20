#include <vector>
#include <fstream>

/**
 * A class that represents the state of the cube. It provides methods to manipulate the cube by turning its faces or turning the whole cube.
 *
 * All rotation are achieved by rearranging the pieces of the cube. This guarantees that the visual representation of the cube is oriented in the same way as the state representation and allows the use of the usual relative notation for turns.
 *
 * The class also provides methods to calculate the moves needed to bring the cube into a given configuration.
 *
 * A simple move stack records all turns to facilitate features like undo, turn animation, saving during tutorials, etc. The move stack has an iterator and it can be saved/loaded.
 *
 * Finally, single pieces can by queried by their position in the current configuration. This allows more complex queries to be written on top of it using lua.
 */
class CubeModel
{
	public:
		/** The possible colors for the faces of a piece. BLACK is also used as a wildcard */
		enum Color {BLACK, BLUE, GREEN, ORANGE, RED, WHITE, YELLOW};
		/** The types of turns on a normal 3x3x3 cube. These are relative to the current cube orientation.*/
		enum Turn {FRONT, BACK, UP, DOWN, LEFT, RIGHT, X_AXIS, Y_AXIS, Z_AXIS};

		/**
		 * Struct representing a single piece of the cube.
		 */
		struct Piece
		{
			/** ID used to identifiy the piece in queries */
			int id;
			/** Color of each face. This is quite redundant, since many faces are never seen, but it makes rendering the cube easy. */
			Color face[6]; //front, back, up, down, left, right
		};

		/**
		 * Struct representing a move.
		 */
		struct Move
		{
			/** Type of move. */
			Turn type;
			/** Turn clockwise it true and counter-clockwise if false */
			bool cw;
		};

		/** Java-style iterator for the move stacks. */
		/*class MoveIterator
		{
			public:
				bool hasNext();
				Move& next();
		};//*/

	private:
		/** Cube data-structure. The center piece is never moved, but included for simplicity. The 3x3x3 cube is small, so rotations are cheap and we don't need an elaborate data-structure here. */
		Piece cube[3][3][3];

		/** The past moves stack. These moves have already been turned. Some features, like "Undo" or requesting an iterator for the last n moves, pop moves from this stack, unturn them and push them on the futureMovesStack. */
		std::vector<Move> pastMovesStack;

		/** The future moves stack. These moves have not been turned, yet. Some features, like "Redo" or requesting the next move from an iterator, pop moves from this stack, turn them and push them back onto the pastMovesStack. */
		std::vector<Move> futureMovesStack;

	public:
		/** Default constructor. */
		CubeModel();

		/** Default deconstructor. */
		~CubeModel();

		/** Resets the cube to its initital (solved) state and optionally clears the move stacks. */
		void reset(bool clear = true);

		/** Saves the the move stack to an already open file. This method assumes that the file's seek pointer is already at the position where the stack should be written. */
		bool save(std::ofstream file);

		/** Loads the move stack from an already open file and replays the stack to bring the cube into the right configuration. This method assumes that the file's seek pointer is at the start of the stack. */
		bool load(std::ifstream file);

		/** Performs the turn specified and automatically pushes/pops the move stack as appropriate. */
		void turn(Turn type, bool cw);

		/** Convinience method. Does the same as turn(Turn type, bool cw). */
		void turn(Move move);

		/** Returns true if the current cube configuration matches the target configuration. This method ignores the global orientation of the cube. */
		bool checkForTarget(Color target[6][9] = 0);

		/** Finds the shortest sequence of turns, that brings the cube into the target configuration. This method ignores the global orientation of the cube. It returns the number of moves in the calculated sequence. If 0 is returned no sequence was found or the target configuration was invalid. This method performs a brute-force search using iterative deepening. It should only be used forshort sequences (e.g. moving a single piece to a target position. To solve the whole cube a more intelligent solving algorithm should be implemented using lua.*/
		int solveForTarget(int maxDepth, Color target[6][9] = 0);

		/** Returns the piece that currently sits at the given coordinates. Coordinates must be from [-1, 0, 1].*/
		Piece& getPiece(int x, int y, int z);
		
		/** Java-style iterator to iterate over the last numMoves moves. If numMoves is 0 or omitted it points to the first move at the bottom of the stack. Calling this method renders previously obtained iterators obsolete. */ 
		//MoveIterator getMoveIterator(int numMoves = 0);


		// implement via lua:
		/*int getPieceID(Color piece[6]);
		int getPieceCoordX(int id);
		int getPieceCoordY(int id);
		int getPieceCoordZ(int id);
		Color getPieceColorX(int id);
		Color getPieceColorY(int id);
		Color getPieceColorZ(int id);//*/
		// scramble
};
