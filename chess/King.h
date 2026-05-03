#ifndef KING_H
#define KING_H

#include "Piece.h"

class King : public Piece {
public:
    King(char sym, bool white) : Piece(sym, white) {}
    bool isValidMove(Board* board, int x, int y, int dx, int dy) override;
    char getType() const override { return 'K'; }
};

#endif