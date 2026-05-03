#ifndef PAWN_H
#define PAWN_H

#include "Piece.h"

class Pawn : public Piece {
public:
    Pawn(char sym, bool white) : Piece(sym, white) {}
    bool isValidMove(Board* board, int x, int y, int dx, int dy) override;
    char getType() const override { return 'P'; }
};

#endif