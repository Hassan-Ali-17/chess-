#include <iostream>
#include <conio.h>
#include "Board.h"
using namespace std;

class ChessGame {
private:
    Board* board;
    bool currentPlayerWhite;
    GUI* gui;

    string getPieceName(char piece) {
        char lower = tolower(piece);
        switch (lower) {
        case 'p': return "Pawn";
        case 'r': return "Rook";
        case 'h': return "Knight";
        case 'b': return "Bishop";
        case 'q': return "Queen";
        case 'k': return "King";
        default: return "Piece";
        }
    }

    void displayCaptureMessage(char capturedPiece) {
        gui->printColoredText("\n💥 CAPTURE! ", GUI::MAGENTA);
        gui->setColor(GUI::YELLOW);
        cout << "You captured a " << getPieceName(capturedPiece) << "!\n";
        gui->resetColor();
    }

    bool checkKingCaptured(char capturedPiece) {
        char lower = tolower(capturedPiece);
        if (lower == 'k') {
            gui->clearScreen();
            gui->printTitle("GAME OVER - KING CAPTURED!", GUI::RED);

            gui->setColor(GUI::YELLOW);
            cout << "\n  ♔ KING HAS BEEN CAPTURED! ♔\n\n";
            gui->resetColor();

            gui->printColoredText("  " + string(currentPlayerWhite ? "PLAYER 1 (GREEN)" : "PLAYER 2 (RED)") + " WINS!\n\n",
                currentPlayerWhite ? GUI::GREEN : GUI::RED);

            gui->printColoredText("  Victory by capturing the King!\n", GUI::YELLOW);
            cout << "\n  Press any key to exit...";
            _getch();
            exit(0);
            return true;
        }
        return false;
    }

    void getCoordinates(int& x, int& y, const string& prompt) {
        gui->setColor(GUI::CYAN);
        cout << (currentPlayerWhite ? "Player 1 (Green)" : "Player 2 (Red)");
        gui->resetColor();
        cout << " - " << prompt << endl;

        gui->setColor(GUI::YELLOW);
        cout << "Click on the board OR enter coordinates:\n";
        cout << "Enter x coordinate (or -1 to use mouse): ";
        gui->resetColor();
        cin >> x;

        if (x == -1) {
            gui->printColoredText("\nClick on a square...\n", GUI::CYAN);
            if (!gui->getMouseClick(x, y)) {
                x = -1;
                y = -1;
            }
        }
        else {
            gui->setColor(GUI::YELLOW);
            cout << "Enter y coordinate: ";
            gui->resetColor();
            cin >> y;
        }
    }

    bool validatePieceSelection(int x, int y) {
        Piece* piece = board->getPiece(x, y);
        if (piece == nullptr) {
            gui->printColoredText("✗ No piece at that position!\n", GUI::RED);
            cout << "Press any key to continue...";
            _getch();
            return false;
        }
        if (piece->getIsWhite() != currentPlayerWhite) {
            gui->printColoredText("✗ Invalid piece. Please select your own piece!\n", GUI::RED);
            cout << "Press any key to continue...";
            _getch();
            return false;
        }
        return true;
    }

    void handlePawnPromotion(int x, int y) {
        Piece* piece = board->getPiece(x, y);
        if (piece == nullptr || piece->getType() != 'P')
            return;

        bool needsPromotion = (currentPlayerWhite && x == 7) || (!currentPlayerWhite && x == 0);

        if (needsPromotion) {
            gui->clearScreen();
            gui->printTitle("PAWN PROMOTION", GUI::MAGENTA);

            cout << "\n";
            gui->printColoredText("  ♕ Your pawn has reached the end! ♕\n\n", GUI::YELLOW);

            gui->setColor(GUI::GREEN);
            cout << "  Choose promotion piece:\n\n";
            gui->resetColor();

            gui->printColoredText("  [Q] ", GUI::CYAN);
            cout << "Queen  - Most powerful piece\n";

            gui->printColoredText("  [R] ", GUI::CYAN);
            cout << "Rook   - Moves horizontally/vertically\n";

            gui->printColoredText("  [B] ", GUI::CYAN);
            cout << "Bishop - Moves diagonally\n";

            gui->printColoredText("  [H] ", GUI::CYAN);
            cout << "Knight - Moves in L-shape\n\n";

            char choice;
            bool validChoice = false;

            while (!validChoice) {
                gui->setColor(GUI::YELLOW);
                cout << "  Enter your choice (Q/R/B/H): ";
                gui->resetColor();
                cin >> choice;
                choice = toupper(choice);

                if (choice == 'Q' || choice == 'R' || choice == 'B' || choice == 'H') {
                    validChoice = true;
                }
                else {
                    gui->printColoredText("\n  ✗ Invalid choice! Please enter Q, R, B, or H.\n\n", GUI::RED);
                }
            }

            board->promotePawn(x, y, choice, currentPlayerWhite);

            cout << "\n  Press any key to continue...";
            _getch();
        }
    }

    bool checkForCheckmate() {
        int kingX, kingY;
        bool opponentWhite = !currentPlayerWhite;

        if (board->findKing(kingX, kingY, opponentWhite)) {
            if (board->isUnderAttack(kingX, kingY, opponentWhite)) {
                if (!board->hasAnyLegalMoves(opponentWhite)) {
                    gui->clearScreen();
                    gui->printTitle("CHECKMATE!", GUI::RED);

                    gui->setColor(GUI::YELLOW);
                    cout << "\n  ♔ GAME OVER ♔\n\n";
                    gui->resetColor();

                    gui->printColoredText("  " + string(currentPlayerWhite ? "PLAYER 1 (GREEN)" : "PLAYER 2 (RED)") + " WINS!\n\n",
                        currentPlayerWhite ? GUI::GREEN : GUI::RED);

                    gui->printColoredText("  The King has been checkmated!\n", GUI::RED);
                    cout << "\n  Press any key to exit...";
                    _getch();
                    exit(0);
                    return true;
                }
                else {
                    gui->printColoredText("\n⚠️  CHECK! The King is under attack!\n", GUI::RED);
                    gui->printColoredText("   You must protect your King!\n\n", GUI::YELLOW);
                }
                return false;
            }
        }
        return false;
    }

    void checkForDraw() {
        bool opponentWhite = !currentPlayerWhite;

        if (board->isStalemate(opponentWhite)) {
            gui->clearScreen();
            gui->printTitle("STALEMATE - DRAW!", GUI::YELLOW);

            gui->setColor(GUI::CYAN);
            cout << "\n  ⚖ GAME DRAWN ⚖\n\n";
            gui->resetColor();

            gui->printColoredText("  The game is a draw by stalemate!\n", GUI::YELLOW);
            gui->printColoredText("  No legal moves available but King is not in check.\n", GUI::WHITE);
            cout << "\n  Press any key to exit...";
            _getch();
            exit(0);
        }

        if (board->isFiftyMoveDraw()) {
            gui->clearScreen();
            gui->printTitle("50-MOVE RULE - DRAW!", GUI::YELLOW);

            gui->setColor(GUI::CYAN);
            cout << "\n  ⚖ GAME DRAWN ⚖\n\n";
            gui->resetColor();

            gui->printColoredText("  The game is a draw by the 50-move rule!\n", GUI::YELLOW);
            gui->printColoredText("  50 moves without a capture or pawn move.\n", GUI::WHITE);
            cout << "\n  Press any key to exit...";
            _getch();
            exit(0);
        }
    }

public:
    ChessGame() {
        board = new Board();
        gui = board->getGUI();
        currentPlayerWhite = false; 
    }

    ~ChessGame() {
        delete board;
    }

    void initialize(const char* filename) {
        board->initialize(filename);
    }

    void play() {
        gui->printTitle("WELCOME TO CHESS", GUI::GREEN);
        cout << "Press any key to start...";
        _getch();

        board->print();

        while (true) {
            gui->setColor(GUI::CYAN);
            cout << "\n########################################\n";
            gui->resetColor();

            gui->printColoredText((currentPlayerWhite ? "  PLAYER 1 (GREEN)" : "  PLAYER 2 (RED)"),
                (currentPlayerWhite ? GUI::GREEN : GUI::RED));
            cout << "'s Turn\n";

            gui->setColor(GUI::CYAN);
            cout << "########################################\n\n";
            gui->resetColor();

            int x, y;
            getCoordinates(x, y, "Select piece to move");

            if (x == -1 || !validatePieceSelection(x, y)) {
                board->print();
                continue;
            }

            board->printWithHighlight(x, y);

            int dx, dy;
            getCoordinates(dx, dy, "Enter destination");

            if (dx == -1) {
                board->print();
                continue;
            }

            board->saveState("previousmove.txt");

            bool captured = false;
            char capturedPiece = '.';

            if (!board->movePiece(x, y, dx, dy, captured, capturedPiece, currentPlayerWhite)) {
                gui->printColoredText("\n✗ Invalid move! Try again.\n", GUI::RED);
                cout << "Press any key to continue...";
                _getch();
                board->print();
                continue;
            }

            if (captured && checkKingCaptured(capturedPiece)) {
                return; 
            }

            handlePawnPromotion(dx, dy);
            board->print();

            if (captured) {
                displayCaptureMessage(capturedPiece);
            }

            gui->setColor(GUI::DARK_GRAY);
            cout << "Move: " << board->getMoveCount() << " | Half-moves since capture/pawn: " << board->getHalfMoveClock() << "\n";
            gui->resetColor();

            checkForCheckmate();
            checkForDraw();

            gui->setColor(GUI::YELLOW);
            cout << "\nDo you want to undo the move? (y/n): ";
            gui->resetColor();

            char choice;
            cin >> choice;
            if (choice == 'y' || choice == 'Y') {
                board->loadState("previousmove.txt");
                gui->printColoredText("\n✓ Move undone.\n", GUI::GREEN);
                cout << "Press any key to continue...";
                _getch();
                board->print();
                continue;
            }

            currentPlayerWhite = !currentPlayerWhite;
        }
    }
};

int main() {
    ChessGame game;
    game.initialize("board.txt");
    game.play();

    cout << "\nThanks for playing!" << endl;
    return 0;
}