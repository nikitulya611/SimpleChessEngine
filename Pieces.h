#ifndef PIECES_H
#define PIECES_H

/*
P - pawn - пешка
R Ч rook Ч ладь€
N Ч knight Ч конь
B Ч bishop Ч слон
Q Ч queen Ч ферзь
K Ч king Ч король
*/
using PIECE_SIZE = short;

struct Masks {
    static const PIECE_SIZE isWhite = 1;
    static const PIECE_SIZE type = ((1 << 3) - 1) << 1;
    static const PIECE_SIZE isMoved = 1 << 5;
    static const PIECE_SIZE isPawnMovedByTwo = 1 << 6;

};

/*
001 - пешка
010 - конь
011 - слон
100 - ладь€
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

struct Cost {
    static const PIECE_SIZE PAWN = 100;
    static const PIECE_SIZE KNIGHT = 280;
    static const PIECE_SIZE BISHOP = 320;
    static const PIECE_SIZE ROOK = 479;
    static const PIECE_SIZE QUEEN = 929;
    static const PIECE_SIZE KING = QUEEN * 8 + 2 * (KNIGHT + BISHOP + ROOK);
};

/*
short - 16 бит
1 - черна€ или бела€
2-3-4 - тип фигуры (6 вариантов)
5- ходила ли (важно дл€ пешек и корол€ с ладь€ми)
6 - ходила ли пешка на 2 пол€ вперед (дл€ вз€ти€ на проходе)

все нули - пустое поле
*/

struct Piece {
    inline bool isWhite() const {
        return data & Masks::isWhite;
    }

    inline bool isBlack() const {
        return !isWhite();
    }

    inline PIECE_SIZE type() const {
        return (data & Masks::type) >> 1;
    }
    inline PIECE_SIZE isMoved() const {
        return data & Masks::isMoved;
    }

    virtual inline int getCost() const {
        return 0;
    }

    PIECE_SIZE data;
    static const int Cost = 0;
};

//пешка
struct PiecePawn : public Piece {
    inline bool isPawnMovedByTwo() const {
        return data & Masks::isPawnMovedByTwo;
    }

    inline int getCost() const {
        return isWhite() ? Cost::PAWN : -Cost::PAWN;
    }
};

//конь
struct PieceKnight : public Piece {

    inline int getCost() const {
        return isWhite() ? Cost::KNIGHT : -Cost::KNIGHT;
    }
};

//слон
struct PieceBishop : public Piece {
    inline int getCost() const {
        return isWhite() ? Cost::BISHOP : -Cost::BISHOP;
    }
};

//ладь€
struct PieceRook : public Piece {
    inline int getCost() const {
        return isWhite() ? Cost::ROOK : -Cost::ROOK;
    }
};

//ферзь
struct PieceQueen : public Piece {
    inline int getCost() const {
        return isWhite() ? Cost::QUEEN : -Cost::QUEEN;
    }
};

//король
struct PieceKing : public Piece {
    inline int getCost() const {
        return isWhite() ? Cost::KING : -Cost::KING;
    }
};


#endif // !PIECES_H
