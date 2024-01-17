#ifndef SIMPLE_CHESS_ENGINE_H
#define SIMPLE_CHESS_ENGINE_H

#include <list>

#include "Board.h"

class SimpleChessEngine {
	SimpleChessEngine(int depth = 3, Board board = Board()) : depth(depth), board(board) {

	}

	void generate(Board currentBoard, DeltaBoard deltaBoard, int alpha = Cost::KING * 2, int beta = -Cost::KING * 2) {
		for (auto piece : currentBoard.getBoard()) {
			switch (piece->type()) {
			case Types::BISHOP:
				//возможный ход
				break;
			default:
				break;
			}
		}
	}

private:
	short depth;
	Board board;
};

#endif // !SIMPLE_CHESS_ENGINE_H
