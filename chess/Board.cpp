#include "Board.h"

bool Board::isUnderAttack(int kingX, int kingY, bool isWhite) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr && board[i][j]->getIsWhite() != isWhite) {
                if (board[i][j]->isValidMove(const_cast<Board*>(this), i, j, kingX, kingY)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool Board::hasAnyLegalMoves(bool isWhite) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr && board[i][j]->getIsWhite() == isWhite) {
                for (int dx = 0; dx < 8; dx++) {
                    for (int dy = 0; dy < 8; dy++) {
                        if (board[i][j]->isValidMove(const_cast<Board*>(this), i, j, dx, dy)) {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool Board::isStalemate(bool isWhite) const {
    int kingX, kingY;
    if (!findKing(kingX, kingY, isWhite))
        return false;

    return !isUnderAttack(kingX, kingY, isWhite) && !hasAnyLegalMoves(isWhite);
}

bool Board::isFiftyMoveDraw() const {
    return halfMoveClock >= 100; 
}

int Board::getMoveCount() const {
    return moveCount;
}

int Board::getHalfMoveClock() const {
    return halfMoveClock;
}

bool Board::canCastle(int x, int y, int dx, int dy, bool isWhite) {
    if ((isWhite && whiteKingMoved) || (!isWhite && blackKingMoved))
        return false;

    bool kingside = (dy > y);

    if (isWhite) {
        if (kingside && whiteRookRightMoved) return false;
        if (!kingside && whiteRookLeftMoved) return false;
    }
    else {
        if (kingside && blackRookRightMoved) return false;
        if (!kingside && blackRookLeftMoved) return false;
    }

    int start = (kingside ? y + 1 : 1);
    int end = (kingside ? 7 : y);
    for (int i = start; i < end; i++) {
        if (board[x][i] != nullptr)
            return false;
    }

    if (isUnderAttack(x, y, isWhite))
        return false;

    int midCol = (kingside ? y + 1 : y - 1);
    if (isUnderAttack(x, midCol, isWhite))
        return false;

    return true;
}

void Board::performCastling(int x, int y, int dx, int dy) {
    bool kingside = (dy > y);

    board[dx][dy] = board[x][y];
    board[x][y] = nullptr;

    if (kingside) {
        board[dx][dy - 1] = board[x][7];
        board[x][7] = nullptr;
    }
    else {
        board[dx][dy + 1] = board[x][0];
        board[x][0] = nullptr;
    }
}
