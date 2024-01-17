#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <array>
#include <algorithm>
#include <numeric>
#include <list>

#include "Pieces.h"


class Board {
public:
    Board() {
        PiecePawn pw, pb;
        pw.data = 0b0000000000000011;
        pb.data = 0b0000000000000010;
        for (int i = 0; i < 8; i++) {
            PiecePawn* p1 = new PiecePawn;
            PiecePawn* p2 = new PiecePawn;
            *p1 = pw;
            *p2 = pb;
            repres[1 * 8 + i] = p2;
            repres[6 * 8 + i] = p1;
        }

        PieceRook rw, rb;
        rw.data = 0b0000000000001001;
        rb.data = 0b0000000000001000;
        for (int i = 0; i < 2; i++) {
            PieceRook* p1 = new PieceRook;
            PieceRook* p2 = new PieceRook;
            *p1 = rw;
            *p2 = rb;
            repres[i * 7] = p2;
            repres[7 * 8 + i * 7] = p1;
        }

        PieceKnight kw, kb;
        kw.data = 0b0000000000000101;
        kb.data = 0b0000000000000100;
        for (int i = 0; i < 2; i++) {
            PieceKnight* p1 = new PieceKnight;
            PieceKnight* p2 = new PieceKnight;
            *p1 = kw;
            *p2 = kb;
            repres[1 + i * 5] = p2;
            repres[7 * 8 + 1 + i * 5] = p1;
        }

        PieceBishop bw, bb;
        bw.data = 0b0000000000000111;
        bb.data = 0b0000000000000110;
        for (int i = 0; i < 2; i++) {
            PieceBishop* p1 = new PieceBishop;
            PieceBishop* p2 = new PieceBishop;
            *p1 = bw;
            *p2 = bb;
            repres[2 + i * 3] = p2;
            repres[7 * 8 + 2 + i * 3] = p1;
        }

        {
            PieceQueen qw, qb;
            qw.data = 0b0000000000001011;
            qb.data = 0b0000000000001010;
            PieceQueen* p1 = new PieceQueen;
            PieceQueen* p2 = new PieceQueen;
            *p1 = qw;
            *p2 = qb;
            repres[3] = p2;
            repres[7 * 8 + 3] = p1;
        }

        {
            PieceKing kw, kb;
            kw.data = 0b0000000000001111;
            kb.data = 0b0000000000001110;
            PieceKing* p1 = new PieceKing;
            PieceKing* p2 = new PieceKing;
            *p1 = kw;
            *p2 = kb;
            repres[4] = p2;
            repres[7 * 8 + 4] = p1;
        }

        for (int i = 16; i < 48; i++)
        {
            Piece* empty = new Piece;
            empty->data = 0;
            repres[i] = empty;
        }
        cost = 0;
    }

    ~Board() {

    }

    void setCost(int newCost) {
        cost = newCost;
    }

    void changeCost(int delta) {
        cost += delta;
    }

    int getCost() const {
        return cost;
    }

    int recalculateEstimate() {
        cost = std::accumulate(repres.begin(), repres.end(), 0, [](int val, Piece* p) {
            return p->getCost() + val;
            });
        return cost;
    }

    std::array<Piece*, 64> getBoard() const {
        return repres;
    }

    friend std::ostream& operator<<(std::ostream& output, const Board& board) {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                switch (board.getBoard()[i * 8 + j]->type()) {
                case Types::EMPTY:
                    output << '#';
                    break;
                case Types::PAWN:
                    if (board.getBoard()[i * 8 + j]->isWhite())
                        output << 'P';
                    else output << 'p';
                    break;
                case Types::KING:
                    if (board.getBoard()[i * 8 + j]->isWhite())
                        output << 'K';
                    else output << 'k';
                    break;
                case Types::ROOK:
                    if (board.getBoard()[i * 8 + j]->isWhite())
                        output << 'R';
                    else output << 'r';
                    break;
                case Types::BISHOP:
                    if (board.getBoard()[i * 8 + j]->isWhite())
                        output << 'B';
                    else output << 'b';
                    break;
                case Types::KNIGHT:
                    if (board.getBoard()[i * 8 + j]->isWhite())
                        output << 'N';
                    else output << 'n';
                    break;
                case Types::QUEEN:
                    if (board.getBoard()[i * 8 + j]->isWhite())
                        output << 'Q';
                    else output << 'q';
                    break;
                default:
                    output << '?';
                }
            }
            output << '\n';

        }
        return output;
    }

private:
    std::array<Piece*, 64> repres;
    int cost;
};

struct DeltaBoard {
    struct Turn {
        int from;
        int to;
        int deltaEstimate;
    };

    std::list<Turn> sequence;
};

#endif // !BOARD_H
