#include <iostream>
#include <array>


/*
P - pawn - пешка
R — rook — ладья
N — knight — конь
B — bishop — слон
Q — queen — ферзь
K — king — король
*/
using PIECE_SIZE = short;

const int COST_P = 100, COST_N = 280, COST_B = 320, COST_R = 479, COST_Q = 929;
const int COST_K = COST_Q * 8 + 2 * (COST_N + COST_B + COST_R);

struct Masks {
	static const PIECE_SIZE isWhite = 1 << 1;
	static const PIECE_SIZE type = ((1 << 3) - 1) << 2;
	static const PIECE_SIZE isMoved = 1 << 5;
	static const PIECE_SIZE isPawnMovedByTwo = 1 << 6;

};

/*
001 - пешка
010 - конь
011 - слон
100 - ладья
101 - ферзь
111 - король
*/

struct Types {
	static const PIECE_SIZE EMPTY = 0;
	static const PIECE_SIZE PAWN = 1;
	static const PIECE_SIZE KNIGHT = 2;
	static const PIECE_SIZE BISHOP = 3;
	static const PIECE_SIZE ROOK = 4;
	static const PIECE_SIZE QUEEN = 5;
	static const PIECE_SIZE KING = 7;

};

/*
short - 16 бит
1 - черная или белая
2-3-4 - тип фигуры (6 вариантов)
5- ходила ли (важно для пешек и короля с ладьями)
6 - ходила ли пешка на 2 поля вперед (для взятия на проходе)

все нули - пустое поле
*/

struct Piece {
	inline bool isWhite() {
		return data & Masks::isWhite;
	}

	inline bool isBlack() {
		return !isWhite();
	}

	inline PIECE_SIZE type() {
		return data & Masks::type;
	}
	inline PIECE_SIZE isMoved() {
		return data & Masks::isMoved;
	}
	
	PIECE_SIZE data;
};

//пешка
struct PiecePawn : public Piece {
	inline bool isPawnMovedByTwo() {
		return data & Masks::isPawnMovedByTwo;
	}
};

//конь
struct PieceKnight : public Piece {

};

//слон
struct PieceBishop : public Piece {

};

//ладья
struct PieceRook : public Piece {

};

//ферзь
struct PieceQueen : public Piece {

};

//король
struct PieceKing : public Piece {

};

using Board = std::array<Piece*, 64>;

void generateInitialPosition(Board& board) {

}

void printBoard(Board& board)
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			switch (board[i * 8 + j]->type()) {
			case Types::EMPTY:
				std::cout << '#';
				break;
			case Types::PAWN:
				std::cout << 'P';
				break;
			}
		}
		std::cout << '\n';
	}
}

int main()
{
	Board board;
	generateInitialPosition(board);
	//printBoard(board);
	std::cout << ((1 << 1) == 2);
}