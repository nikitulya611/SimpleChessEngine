#ifndef PIECES_H
#define PIECES_H

/*
P - pawn - �����
R � rook � �����
N � knight � ����
B � bishop � ����
Q � queen � �����
K � king � ������
*/
using PIECE_SIZE = short;

struct Masks {
    static const PIECE_SIZE isWhite = 1;
    static const PIECE_SIZE type = ((1 << 3) - 1) << 1;
    static const PIECE_SIZE isMoved = 1 << 5;
    static const PIECE_SIZE isPawnMovedByTwo = 1 << 6;

};

/*
001 - �����
010 - ����
011 - ����
100 - �����
101 - �����
111 - ������
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
short - 16 ���
1 - ������ ��� �����
2-3-4 - ��� ������ (6 ���������)
5- ������ �� (����� ��� ����� � ������ � �������)
6 - ������ �� ����� �� 2 ���� ������ (��� ������ �� �������)

��� ���� - ������ ����
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

//�����
struct PiecePawn : public Piece {
    inline bool isPawnMovedByTwo() const {
        return data & Masks::isPawnMovedByTwo;
    }

    inline int getCost() const {
        return isWhite() ? Cost::PAWN : -Cost::PAWN;
    }
};

//����
struct PieceKnight : public Piece {

    inline int getCost() const {
        return isWhite() ? Cost::KNIGHT : -Cost::KNIGHT;
    }
};

//����
struct PieceBishop : public Piece {
    inline int getCost() const {
        return isWhite() ? Cost::BISHOP : -Cost::BISHOP;
    }
};

//�����
struct PieceRook : public Piece {
    inline int getCost() const {
        return isWhite() ? Cost::ROOK : -Cost::ROOK;
    }
};

//�����
struct PieceQueen : public Piece {
    inline int getCost() const {
        return isWhite() ? Cost::QUEEN : -Cost::QUEEN;
    }
};

//������
struct PieceKing : public Piece {
    inline int getCost() const {
        return isWhite() ? Cost::KING : -Cost::KING;
    }
};


#endif // !PIECES_H
