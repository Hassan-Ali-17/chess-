//#ifndef BOARD_H
//#define BOARD_H
//
//#include <iostream>
//#include <fstream>
//#include "Piece.h"
//#include "Pawn.h"
//#include "Rook.h"
//#include "Knight.h"
//#include "Bishop.h"
//#include "Queen.h"
//#include "King.h"
//#include "GUI.h"
//
//class Board {
//private:
//    static const int ROWS = 8;
//    static const int COLS = 8;
//    Piece* board[8][8];
//    GUI* gui;
//
//    Piece* createPiece(char symbol) {
//        bool isWhite = (symbol >= 'A' && symbol <= 'Z');
//        char lower = isWhite ? symbol + 32 : symbol;
//
//        switch (lower) {
//        case 'p': return new Pawn(symbol, isWhite);
//        case 'r': return new Rook(symbol, isWhite);
//        case 'h': return new Knight(symbol, isWhite);
//        case 'b': return new Bishop(symbol, isWhite);
//        case 'q': return new Queen(symbol, isWhite);
//        case 'k': return new King(symbol, isWhite);
//        default: return nullptr;
//        }
//    }
//
//public:
//    Board() {
//        gui = new GUI();
//        for (int i = 0; i < ROWS; i++) {
//            for (int j = 0; j < COLS; j++) {
//                board[i][j] = nullptr;
//            }
//        }
//    }
//
//    ~Board() {
//        for (int i = 0; i < ROWS; i++) {
//            for (int j = 0; j < COLS; j++) {
//                delete board[i][j];
//            }
//        }
//        delete gui;
//    }
//
//    void initialize(const char* filename) {
//        std::ifstream reader(filename);
//        char symbol;
//
//        for (int i = 0; i < ROWS; i++) {
//            for (int j = 0; j < COLS; j++) {
//                reader >> symbol;
//                if (symbol == '.') {
//                    board[i][j] = nullptr;
//                }
//                else {
//                    board[i][j] = createPiece(symbol);
//                }
//            }
//        }
//        reader.close();
//    }
//
//    void print() const {
//        gui->clearScreen();
//        gui->printTitle("CHESS GAME", GUI::CYAN);
//
//        std::cout << "     ";
//        for (int j = 0; j < COLS; j++) {
//            gui->setColor(GUI::YELLOW);
//            std::cout << j << "   ";
//        }
//        gui->resetColor();
//        std::cout << std::endl;
//
//        std::cout << "   #################################" << std::endl;
//
//        for (int i = 0; i < ROWS; i++) {
//            gui->setColor(GUI::YELLOW);
//            std::cout << " " << i << " ";
//            gui->resetColor();
//            std::cout << "#";
//
//            for (int j = 0; j < COLS; j++) {
//                int bgColor = ((i + j) % 2 == 0) ? GUI::DARK_GRAY : GUI::BLACK;
//
//                if (board[i][j] != nullptr) {
//                    char symbol = board[i][j]->getSymbol();
//                    int textColor = board[i][j]->getIsWhite() ? GUI::GREEN : GUI::RED;
//
//                    gui->setColor(textColor, bgColor);
//                    std::cout << " " << symbol << " ";
//                    gui->resetColor();
//                }
//                else {
//                    gui->setColor(GUI::DARK_GRAY, bgColor);
//                    std::cout << "   ";
//                    gui->resetColor();
//                }
//                std::cout << "#";
//            }
//            std::cout << std::endl;
//
//            if (i < ROWS - 1) {
//                std::cout << "   #################################" << std::endl;
//            }
//        }
//
//        std::cout << "   #################################" << std::endl;
//        std::cout << std::endl;
//    }
//
//    bool isEmpty(int x, int y) const {
//        if (x < 0 || x >= ROWS || y < 0 || y >= COLS)
//            return false;
//        return board[x][y] == nullptr;
//    }
//
//    bool isEnemy(int x, int y, bool isWhite) const {
//        if (isEmpty(x, y))
//            return false;
//        return board[x][y]->getIsWhite() != isWhite;
//    }
//
//    Piece* getPiece(int x, int y) const {
//        if (x < 0 || x >= ROWS || y < 0 || y >= COLS)
//            return nullptr;
//        return board[x][y];
//    }
//
//    bool movePiece(int x, int y, int dx, int dy, bool& captured, char& capturedPiece) {
//        captured = false;
//        capturedPiece = '.';
//
//        if (board[x][y] == nullptr)
//            return false;
//
//        if (dx < 0 || dx >= ROWS || dy < 0 || dy >= COLS)
//            return false;
//
//        if (!board[x][y]->isValidMove(this, x, y, dx, dy))
//            return false;
//
//        if (board[dx][dy] != nullptr) {
//            captured = true;
//            capturedPiece = board[dx][dy]->getSymbol();
//        }
//
//        delete board[dx][dy];
//        board[dx][dy] = board[x][y];
//        board[x][y] = nullptr;
//
//        return true;
//    }
//
//    void promotePawn(int x, int y, char choice, bool isWhite) {
//        delete board[x][y];
//        char symbol = isWhite ? (choice >= 'a' ? choice - 32 : choice) :
//            (choice >= 'A' ? choice + 32 : choice);
//        board[x][y] = createPiece(symbol);
//
//        gui->printColoredText("\n✓ Pawn promoted successfully!\n", GUI::GREEN);
//    }
//
//    bool findKing(int& kingX, int& kingY, bool isWhite) const {
//        char king = isWhite ? 'K' : 'k';
//        for (int i = 0; i < ROWS; i++) {
//            for (int j = 0; j < COLS; j++) {
//                if (board[i][j] != nullptr && board[i][j]->getSymbol() == king) {
//                    kingX = i;
//                    kingY = j;
//                    return true;
//                }
//            }
//        }
//        return false;
//    }
//
//    bool isUnderAttack(int kingX, int kingY, bool isWhite) const;
//
//    bool hasAnyLegalMoves(bool isWhite) const;
//
//    void saveState(const char* filename) const {
//        std::ofstream writer(filename);
//        for (int i = 0; i < ROWS; i++) {
//            for (int j = 0; j < COLS; j++) {
//                if (board[i][j] != nullptr) {
//                    writer << board[i][j]->getSymbol();
//                }
//                else {
//                    writer << ".";
//                }
//                writer << " ";
//            }
//            writer << std::endl;
//        }
//        writer.close();
//    }
//
//    void loadState(const char* filename) {
//        for (int i = 0; i < ROWS; i++) {
//            for (int j = 0; j < COLS; j++) {
//                delete board[i][j];
//                board[i][j] = nullptr;
//            }
//        }
//        initialize(filename);
//    }
//
//    GUI* getGUI() { return gui; }
//};
//
//#endif

#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <fstream>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "GUI.h"

class Board {
private:
    static const int ROWS = 8;
    static const int COLS = 8;
    Piece* board[8][8];
    GUI* gui;

    int enPassantCol;
    int enPassantRow;
    bool whiteKingMoved;
    bool blackKingMoved;
    bool whiteRookLeftMoved;
    bool whiteRookRightMoved;
    bool blackRookLeftMoved;
    bool blackRookRightMoved;
    int moveCount;
    int halfMoveClock; 

    Piece* createPiece(char symbol) {
        bool isWhite = (symbol >= 'A' && symbol <= 'Z');
        char lower = isWhite ? symbol + 32 : symbol;

        switch (lower) {
        case 'p': return new Pawn(symbol, isWhite);
        case 'r': return new Rook(symbol, isWhite);
        case 'h': return new Knight(symbol, isWhite);
        case 'b': return new Bishop(symbol, isWhite);
        case 'q': return new Queen(symbol, isWhite);
        case 'k': return new King(symbol, isWhite);
        default: return nullptr;
        }
    }

public:
    Board() {
        gui = new GUI();
        enPassantCol = -1;
        enPassantRow = -1;
        whiteKingMoved = false;
        blackKingMoved = false;
        whiteRookLeftMoved = false;
        whiteRookRightMoved = false;
        blackRookLeftMoved = false;
        blackRookRightMoved = false;
        moveCount = 0;
        halfMoveClock = 0;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                board[i][j] = nullptr;
            }
        }
    }

    ~Board() {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                delete board[i][j];
            }
        }
        delete gui;
    }

    void initialize(const char* filename) {
        std::ifstream reader(filename);
        char symbol;

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                reader >> symbol;
                if (symbol == '.') {
                    board[i][j] = nullptr;
                }
                else {
                    board[i][j] = createPiece(symbol);
                }
            }
        }
        reader.close();
    }

    void print() const {
        gui->clearScreen();
        gui->printTitle("CHESS GAME", GUI::CYAN);

        gui->setColor(GUI::YELLOW);
        std::cout << "\n  Click on pieces to move them!\n";
        std::cout << "  Press ESC to cancel selection\n\n";
        gui->resetColor();

        std::cout << "     ";
        for (int j = 0; j < COLS; j++) {
            gui->setColor(GUI::YELLOW);
            std::cout << j << "   ";
        }
        gui->resetColor();
        std::cout << std::endl;

        std::cout << "   #################################" << std::endl;

        for (int i = 0; i < ROWS; i++) {
            gui->setColor(GUI::YELLOW);
            std::cout << " " << i << " ";
            gui->resetColor();
            std::cout << "#";

            for (int j = 0; j < COLS; j++) {
                int bgColor = ((i + j) % 2 == 0) ? GUI::DARK_GRAY : GUI::BLACK;

                if (board[i][j] != nullptr) {
                    char symbol = board[i][j]->getSymbol();
                    int textColor = board[i][j]->getIsWhite() ? GUI::GREEN : GUI::RED;

                    gui->setColor(textColor, bgColor);
                    std::cout << " " << symbol << " ";
                    gui->resetColor();
                }
                else {
                    gui->setColor(GUI::DARK_GRAY, bgColor);
                    std::cout << "   ";
                    gui->resetColor();
                }
                std::cout << "#";
            }
            std::cout << std::endl;

            if (i < ROWS - 1) {
                std::cout << "   #################################" << std::endl;
            }
        }

        std::cout << "   #################################" << std::endl;
        std::cout << std::endl;
    }

    void printWithHighlight(int hx, int hy) const {
        gui->clearScreen();
        gui->printTitle("CHESS GAME", GUI::CYAN);

        gui->setColor(GUI::YELLOW);
        std::cout << "\n  Selected piece at (" << hx << ", " << hy << ")\n";
        std::cout << "  Click destination square\n\n";
        gui->resetColor();

        std::cout << "     ";
        for (int j = 0; j < COLS; j++) {
            gui->setColor(GUI::YELLOW);
            std::cout << j << "   ";
        }
        gui->resetColor();
        std::cout << std::endl;

        std::cout << "   #################################" << std::endl;

        for (int i = 0; i < ROWS; i++) {
            gui->setColor(GUI::YELLOW);
            std::cout << " " << i << " ";
            gui->resetColor();
            std::cout << "#";

            for (int j = 0; j < COLS; j++) {
                int bgColor;
                if (i == hx && j == hy) {
                    bgColor = GUI::BLUE; 
                }
                else {
                    bgColor = ((i + j) % 2 == 0) ? GUI::DARK_GRAY : GUI::BLACK;
                }

                if (board[i][j] != nullptr) {
                    char symbol = board[i][j]->getSymbol();
                    int textColor = board[i][j]->getIsWhite() ? GUI::GREEN : GUI::RED;

                    gui->setColor(textColor, bgColor);
                    std::cout << " " << symbol << " ";
                    gui->resetColor();
                }
                else {
                    gui->setColor(GUI::DARK_GRAY, bgColor);
                    std::cout << "   ";
                    gui->resetColor();
                }
                std::cout << "#";
            }
            std::cout << std::endl;

            if (i < ROWS - 1) {
                std::cout << "   #################################" << std::endl;
            }
        }

        std::cout << "   #################################" << std::endl;
        std::cout << std::endl;
    }

    bool isEmpty(int x, int y) const {
        if (x < 0 || x >= ROWS || y < 0 || y >= COLS)
            return false;
        return board[x][y] == nullptr;
    }

    bool isEnemy(int x, int y, bool isWhite) const {
        if (isEmpty(x, y))
            return false;
        return board[x][y]->getIsWhite() != isWhite;
    }

    Piece* getPiece(int x, int y) const {
        if (x < 0 || x >= ROWS || y < 0 || y >= COLS)
            return nullptr;
        return board[x][y];
    }

    bool movePiece(int x, int y, int dx, int dy, bool& captured, char& capturedPiece, bool isWhite) {
        captured = false;
        capturedPiece = '.';

        if (board[x][y] == nullptr)
            return false;

        if (dx < 0 || dx >= ROWS || dy < 0 || dy >= COLS)
            return false;

        if (board[x][y]->getType() == 'K' && abs(dy - y) == 2) {
            if (canCastle(x, y, dx, dy, isWhite)) {
                performCastling(x, y, dx, dy);
                moveCount++;
                halfMoveClock++;
                enPassantCol = -1;
                enPassantRow = -1;
                return true;
            }
            return false;
        }

        if (!board[x][y]->isValidMove(this, x, y, dx, dy))
            return false;

        bool isEnPassant = false;
        if (board[x][y]->getType() == 'P' && dy != y && board[dx][dy] == nullptr) {
            if (enPassantCol != -1 && enPassantRow != -1) {
                if (dy == enPassantCol && x == enPassantRow) {
                    isEnPassant = true;
                    captured = true;
                    capturedPiece = board[enPassantRow][enPassantCol]->getSymbol();
                    delete board[enPassantRow][enPassantCol];
                    board[enPassantRow][enPassantCol] = nullptr;
                }
            }
        }

        if (board[dx][dy] != nullptr && !isEnPassant) {
            captured = true;
            capturedPiece = board[dx][dy]->getSymbol();
        }

        if (captured || board[x][y]->getType() == 'P') {
            halfMoveClock = 0;
        }
        else {
            halfMoveClock++;
        }

        if (board[x][y]->getType() == 'K') {
            if (isWhite) whiteKingMoved = true;
            else blackKingMoved = true;
        }
        if (board[x][y]->getType() == 'R') {
            if (isWhite) {
                if (y == 0) whiteRookLeftMoved = true;
                if (y == 7) whiteRookRightMoved = true;
            }
            else {
                if (y == 0) blackRookLeftMoved = true;
                if (y == 7) blackRookRightMoved = true;
            }
        }

        char pieceType = board[x][y]->getType();

        bool wasTwoSquarePawnMove = false;
        if (pieceType == 'P' && abs(dx - x) == 2) {
            wasTwoSquarePawnMove = true;
        }

        enPassantCol = -1;
        enPassantRow = -1;

        if (wasTwoSquarePawnMove) {
            enPassantCol = dy;
            enPassantRow = dx;
        }

        delete board[dx][dy];
        board[dx][dy] = board[x][y];
        board[x][y] = nullptr;

        moveCount++;
        return true;
    }

    void promotePawn(int x, int y, char choice, bool isWhite) {
        delete board[x][y];
        char symbol = isWhite ? (choice >= 'a' ? choice - 32 : choice) :
            (choice >= 'A' ? choice + 32 : choice);
        board[x][y] = createPiece(symbol);

        gui->printColoredText("\n✓ Pawn promoted successfully!\n", GUI::GREEN);
    }

    bool findKing(int& kingX, int& kingY, bool isWhite) const {
        char king = isWhite ? 'K' : 'k';
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] != nullptr && board[i][j]->getSymbol() == king) {
                    kingX = i;
                    kingY = j;
                    return true;
                }
            }
        }
        return false;
    }

    bool isUnderAttack(int kingX, int kingY, bool isWhite) const;

    bool hasAnyLegalMoves(bool isWhite) const;

    bool isStalemate(bool isWhite) const;

    bool isFiftyMoveDraw() const;

    int getMoveCount() const;

    int getHalfMoveClock() const;

    bool canCastle(int x, int y, int dx, int dy, bool isWhite);

    void performCastling(int x, int y, int dx, int dy);

    void saveState(const char* filename) const {
        std::ofstream writer(filename);
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                if (board[i][j] != nullptr) {
                    writer << board[i][j]->getSymbol();
                }
                else {
                    writer << ".";
                }
                writer << " ";
            }
            writer << std::endl;
        }
        writer.close();
    }

    void loadState(const char* filename) {
        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                delete board[i][j];
                board[i][j] = nullptr;
            }
        }
        initialize(filename);
    }

    GUI* getGUI() { return gui; }
};

#endif