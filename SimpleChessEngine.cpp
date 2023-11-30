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
	static const PIECE_SIZE isWhite = 1;
	//static const PIECE_SIZE type = ((1 << 3) - 1) << 2;
	//static const PIECE_SIZE type = 7 << 1;
	static const PIECE_SIZE type = ((1 << 3) - 1) << 1;
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
		return (data & Masks::type) >> 1;
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
	PiecePawn pw, pb;
	pw.data = 0b0000000000000011;
	pb.data = 0b0000000000000010;
	for (int i = 0; i < 8; i++) {
		PiecePawn* p1 = new PiecePawn;
		PiecePawn* p2 = new PiecePawn;
		*p1 = pw;
		*p2 = pb;
		board[1 * 8 + i] = p2;
		board[6 * 8 + i] = p1;
	}

	PieceRook rw, rb;
	rw.data = 0b0000000000001001;
	rb.data = 0b0000000000001000;
	for (int i = 0; i < 2; i++) {
		PieceRook* p1 = new PieceRook;
		PieceRook* p2 = new PieceRook;
		*p1 = rw;
		*p2 = rb;
		board[i * 7] = p2;
		board[7 * 8 + i * 7] = p1;
	}

	PieceKnight kw, kb;
	kw.data = 0b0000000000000101;
	kb.data = 0b0000000000000100;
	for (int i = 0; i < 2; i++) {
		PieceKnight* p1 = new PieceKnight;
		PieceKnight* p2 = new PieceKnight;
		*p1 = kw;
		*p2 = kb;
		board[1 + i * 5] = p2;
		board[7 * 8 + 1 + i * 5] = p1;
	}

	PieceBishop bw, bb;
	bw.data = 0b0000000000000111;
	bb.data = 0b0000000000000110;
	for (int i = 0; i < 2; i++) {
		PieceBishop* p1 = new PieceBishop;
		PieceBishop* p2 = new PieceBishop;
		*p1 = bw;
		*p2 = bb;
		board[2 + i * 3] = p2;
		board[7 * 8 + 2 + i * 3] = p1;
	}

	{
		PieceQueen qw, qb;
		qw.data = 0b0000000000001011;
		qb.data = 0b0000000000001010;
		PieceQueen* p1 = new PieceQueen;
		PieceQueen* p2 = new PieceQueen;
		*p1 = qw;
		*p2 = qb;
		board[3] = p2;
		board[7 * 8 + 3] = p1;
	}

	{
		PieceKing kw, kb;
		kw.data = 0b0000000000001111;
		kb.data = 0b0000000000001110;
		PieceKing* p1 = new PieceKing;
		PieceKing* p2 = new PieceKing;
		*p1 = kw;
		*p2 = kb;
		board[4] = p2;
		board[7 * 8 + 4] = p1;
	}

	for (int i = 16; i < 48; i++)
	{
		Piece* empty = new Piece;
		empty->data = 0;
		board[i] = empty;
	}

}

void printBoard(Board& board) {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			switch (board[i * 8 + j]->type()) {
			case Types::EMPTY:
				std::cout << '#';
				break;
			case Types::PAWN:
				if(board[i * 8 + j]->isWhite())
					std::cout << 'P';
				else std::cout << 'p';
				break;
			case Types::KING:
				if (board[i * 8 + j]->isWhite())
					std::cout << 'K';
				else std::cout << 'k';
				break;
			case Types::ROOK:
				if (board[i * 8 + j]->isWhite())
					std::cout << 'R';
				else std::cout << 'r';
				break;
			case Types::BISHOP:
				if (board[i * 8 + j]->isWhite())
					std::cout << 'B';
				else std::cout << 'b';
				break;
			case Types::KNIGHT:
				if (board[i * 8 + j]->isWhite())
					std::cout << 'N';
				else std::cout << 'n';
				break;
			case Types::QUEEN:
				if (board[i * 8 + j]->isWhite())
					std::cout << 'Q';
				else std::cout << 'q';
				break;
			default:
				std::cout << '?';
			}
		}
		std::cout << '\n';
	}
}

int main()
{
	Board board;	

	generateInitialPosition(board);
	printBoard(board);


}