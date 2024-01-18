#ifndef SIMPLE_CHESS_ENGINE_H
#define SIMPLE_CHESS_ENGINE_H

#include "Board.h"

inline bool isDivisibleBy8(int num) {
    return !(num & 7);
}

class SimpleChessEngine {
    SimpleChessEngine(int depth = 3, Board board = Board()) : depth(depth), board(board) {

    }

    //в комментариях направление (право/лево) указано с точки зрения белых
    void generate(Board currentBoard, DeltaBoard deltaBoard, int alpha = Cost::KING * 2, int beta = -Cost::KING * 2, short currentDepth = 1) {
        for (size_t i = 0; i < currentBoard.getBoard().size(); ++i) {
            Piece *current = currentBoard.getBoard().at(i);
            bool isWhite = current->isWhite();

            size_t temp;
            switch (current->type()) {
            case Types::PAWN:
                if (current->isWhite()) {
                    if (!current->isMoved() && (i - 16) >= 0 && currentBoard.getBoard().at(i - 16)->type() == Types::EMPTY) {//ход на две клетки вперед белыми

                    }
                    if (currentBoard.getBoard().at(i - 8)->type() == Types::EMPTY) {//ход на одну клетку вперед белыми

                    }
                    if (!isDivisibleBy8(i + 1) && currentBoard.getBoard().at(i - 8 + 1)->isBlack()) {//взятие направо белыми

                    }
                    if (!isDivisibleBy8(i) && currentBoard.getBoard().at(i - 8 - 1)->isBlack()) {//взятие налево белыми

                    }

                } else {
                    if (!current->isMoved() && (i + 16) < 64 && currentBoard.getBoard().at(i + 16)->type() == Types::EMPTY) {//ход на две клетки вперед черными

                    }
                    if (currentBoard.getBoard().at(i + 8)->type() == Types::EMPTY) {//ход на одну клетку вперед черными

                    }
                    if (!isDivisibleBy8(i + 1) && currentBoard.getBoard().at(i + 8 + 1)->isWhite()) {//взятие направо черными

                    }
                    if (!isDivisibleBy8(i) && currentBoard.getBoard().at(i + 8 - 1)->isWhite()) {//взятие налево черными

                    }
                }

                break;
            case Types::ROOK:
                temp = i;
                while (!isDivisibleBy8(temp + 9) && temp + 9 < 64) {// вправо вниз
                    temp += 9;
                    if (currentBoard.getBoard().at(temp)->type() != Types::EMPTY) {
                        if (currentBoard.getBoard().at(temp)->isWhite() == isWhite) {
                            break;
                        }
                        //вражеская фигура
                    }
                    //пустая клетка
                }
                temp = i;
                while (!isDivisibleBy8(temp - 7) && temp - 9 < 64) {// вправо вверх
                    temp -= 7;
                    if (currentBoard.getBoard().at(temp)->type() != Types::EMPTY) {
                        if (currentBoard.getBoard().at(temp)->isWhite() == isWhite) {
                            break;
                        }
                        //вражеская фигура
                    }
                    //пустая клетка
                }

                break;
            case Types::BISHOP:
                temp = i;
                while (temp += 8 < 64) {//по вертикали вниз
                    if (currentBoard.getBoard().at(temp)->type() != Types::EMPTY) {
                        if (currentBoard.getBoard().at(temp)->isWhite() == isWhite) {
                            break;
                        }
                        //вражеская фигура
                    }
                    //пустая клетка
                }
                temp = i;
                while (temp -= 8 >= 0) {//по вертикали вверх
                    if (currentBoard.getBoard().at(temp)->type() != Types::EMPTY) {
                        if (currentBoard.getBoard().at(temp)->isWhite() == isWhite) {
                            break;
                        }
                        //вражеская фигура
                    }
                    //пустая клетка
                }
                temp = i + 1;
                while (!isDivisibleBy8(temp++)) {//по горизонтали вправо
                    if (currentBoard.getBoard().at(temp)->type() != Types::EMPTY) {
                        if (currentBoard.getBoard().at(temp)->isWhite() == isWhite) {
                            break;
                        }
                        //вражеская фигура
                    }
                    //пустая клетка
                }
                temp = i;
                while (!isDivisibleBy8(--temp + 1)) {//по горизонтали влево
                    if (currentBoard.getBoard().at(temp)->type() != Types::EMPTY) {
                        if (currentBoard.getBoard().at(temp)->isWhite() == isWhite) {
                            break;
                        }
                        //вражеская фигура
                    }
                    //пустая клетка
                }


                break;
            }
        }
    }

private:
    short depth;
    Board board;
};

#endif // !SIMPLE_CHESS_ENGINE_H
