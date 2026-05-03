#ifndef ROOK_H
#define ROOK_H

#include "Piece.h"

class Rook : public Piece {
public:
    Rook(char sym, bool white) : Piece(sym, white) {}
    bool isValidMove(Board* board, int x, int y, int dx, int dy) override;
    char getType() const override { return 'R'; }
};

#endif