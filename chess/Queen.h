#ifndef QUEEN_H
#define QUEEN_H

#include "Piece.h"

class Queen : public Piece {
public:
    Queen(char sym, bool white) : Piece(sym, white) {}
    bool isValidMove(Board* board, int x, int y, int dx, int dy) override;
    char getType() const override { return 'Q'; }
};

#endif