#ifndef PIECE_H
#define PIECE_H

class Piece {
protected:
    char symbol;
    bool isWhite;

public:
    Piece(char sym, bool white) : symbol(sym), isWhite(white) {}
    virtual ~Piece() {}

    char getSymbol() const { return symbol; }
    bool getIsWhite() const { return isWhite; }
    void setSymbol(char sym) { symbol = sym; }

    virtual bool isValidMove(class Board* board, int x, int y, int dx, int dy) = 0;
    virtual char getType() const = 0;
};

#endif