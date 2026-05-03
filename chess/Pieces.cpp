#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"

bool Pawn::isValidMove(Board* board, int x, int y, int dx, int dy) {
    if (isWhite) {
        if (x == 1) {
            if ((dx == x + 2 || dx == x + 1) && y == dy &&
                board->isEmpty(x + 1, y) && board->isEmpty(dx, dy))
                return true;
        }

        if (dx == x + 1 && dy == y && board->isEmpty(dx, dy)) {
            return true;
        }

        if (dx == x + 1 && (dy == y - 1 || dy == y + 1)) {
            if (board->isEnemy(dx, dy, isWhite)) {
                return true;
            }
            if (board->isEmpty(dx, dy)) {
                return true;
            }
        }
    }
    else {
        if (x == 6) {
            if ((dx == x - 2 || dx == x - 1) && y == dy &&
                board->isEmpty(x - 1, y) && board->isEmpty(dx, dy))
                return true;
        }

        if (dx == x - 1 && dy == y && board->isEmpty(dx, dy)) {
            return true;
        }

        if (dx == x - 1 && (dy == y + 1 || dy == y - 1)) {
            if (board->isEnemy(dx, dy, isWhite)) {
                return true;
            }
            if (board->isEmpty(dx, dy)) {
                return true;
            }
        }
    }
    return false;
}

bool Rook::isValidMove(Board* board, int x, int y, int dx, int dy) {
    if (x == dx) {
        int start = y < dy ? y + 1 : dy + 1;
        int end = y > dy ? y : dy;
        for (int i = start; i < end; i++) {
            if (!board->isEmpty(x, i))
                return false;
        }
        return true;
    }
    else if (y == dy) {
        int start = x < dx ? x + 1 : dx + 1;
        int end = x > dx ? x : dx;
        for (int i = start; i < end; i++) {
            if (!board->isEmpty(i, y))
                return false;
        }
        return true;
    }
    return false;
}

bool Knight::isValidMove(Board* board, int x, int y, int dx, int dy) {
    if ((dx == x + 2 && (dy == y + 1 || dy == y - 1)) ||
        (dx == x - 2 && (dy == y + 1 || dy == y - 1)) ||
        (dy == y + 2 && (dx == x + 1 || dx == x - 1)) ||
        (dy == y - 2 && (dx == x + 1 || dx == x - 1))) {
        if (board->isEmpty(dx, dy) || board->isEnemy(dx, dy, isWhite)) {
            return true;
        }
    }
    return false;
}

bool Bishop::isValidMove(Board* board, int x, int y, int dx, int dy) {
    if ((dx - x == dy - y) || (dx - x == y - dy)) {
        int xStep = (dx > x) ? 1 : -1;
        int yStep = (dy > y) ? 1 : -1;
        for (int i = x + xStep, j = y + yStep; i != dx; i += xStep, j += yStep) {
            if (!board->isEmpty(i, j))
                return false;
        }
        return true;
    }
    return false;
}

bool Queen::isValidMove(Board* board, int x, int y, int dx, int dy) {
    if (x == dx) {
        int start = y < dy ? y + 1 : dy + 1;
        int end = y > dy ? y : dy;
        for (int i = start; i < end; i++) {
            if (!board->isEmpty(x, i))
                return false;
        }
        return true;
    }
    else if (y == dy) {
        int start = x < dx ? x + 1 : dx + 1;
        int end = x > dx ? x : dx;
        for (int i = start; i < end; i++) {
            if (!board->isEmpty(i, y))
                return false;
        }
        return true;
    }
    else if ((dx - x == dy - y) || (dx - x == y - dy)) {
        int xStep = (dx > x) ? 1 : -1;
        int yStep = (dy > y) ? 1 : -1;
        for (int i = x + xStep, j = y + yStep; i != dx; i += xStep, j += yStep) {
            if (!board->isEmpty(i, j))
                return false;
        }
        return true;
    }
    return false;
}

bool King::isValidMove(Board* board, int x, int y, int dx, int dy) {
    if ((dx - x >= -1 && dx - x <= 1) && (dy - y >= -1 && dy - y <= 1)) {
        if (board->isEmpty(dx, dy) || board->isEnemy(dx, dy, isWhite)) {
            return true;
        }
    }
    return false;
}