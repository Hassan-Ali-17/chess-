#ifndef BISHOP_H
#define BISHOP_H

#include "Piece.h"

class Bishop : public Piece {
public:
    Bishop(char sym, bool white) : Piece(sym, white) {}
    bool isValidMove(Board* board, int x, int y, int dx, int dy) override;
    char getType() const override { return 'B'; }
};

#endif
