#include <iostream>
#include <fstream>
using namespace std;

const int rows = 8;
const int cols = 8;

char** createBoard() {
    char** board = new char* [rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new char[cols];
    }
    return board;
}

void deleteBoard(char** board) {
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
    }
    delete[] board;
}

void boardInitialization(char** board) {
    ifstream reader("board.txt");

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            reader >> board[i][j];
        }
    }
    reader.close();
}

void printBoard(char** board) {
    cout << "  0   1   2   3   4   5   6   7" << endl;
    for (int i = 0; i < rows; i++) {
        cout << i << " ";
        for (int j = 0; j < cols; j++) {
            cout << board[i][j] << " | ";
        }
        cout << endl << "---------------------------------" << endl;
    }
}

void saveBoardState(char** board, const char* filename) {
    ofstream writer("currentMove.txt");
    if (writer.is_open()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                writer << board[i][j] << " ";
            }
            writer << endl;
        }
        writer.close();
    }
}

void loadBoardState(char** board, const char* filename) {
    ifstream reader("previousmove.txt");
    if (reader.is_open()) {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                reader >> board[i][j];
            }
        }
        reader.close();
    }
}

bool undoMove(char** board) {
    ifstream previousMove("previousmove.txt");
    if (!previousMove.is_open()) {
        cout << "No previous move to undo." << endl;
        return false;
    }

    loadBoardState(board, "previousMove.txt");

    saveBoardState(board, "currentMove.txt");

    cout << "Undo successful! Reverted to the previous move." << endl;
    return true;
}

void source(int& x, int& y, int turn) {
    if (turn == 1) {
        cout << "Player 1: Enter your x coordinate: ";
        cin >> x;
        cout << "Player 1: Enter your y coordinate: ";
        cin >> y;
    }
    else {
        cout << "Player 2: Enter your x coordinate: ";
        cin >> x;
        cout << "Player 2: Enter your y coordinate: ";
        cin >> y;
    }
}

void destination(int& x, int& y, int turn) {
    if (turn == 1) {
        cout << "Player 1: Enter the position (x): ";
        cin >> x;
        cout << "Player 1: Enter the position (y): ";
        cin >> y;
    }
    else {
        cout << "Player 2: Enter the position (x): ";
        cin >> x;
        cout << "Player 2: Enter the position (y): ";
        cin >> y;
    }
}

char player(char** board, int x, int y) {
    return board[x][y];
}

bool pawnvalidmove1(char** board, int x, int y, int dx, int dy) {
    if (x == 6) {
        if ((dx == x - 2 || dx == x - 1) && y == dy && board[x - 1][y] == '.' && board[dx][dy] == '.')
            return true;
    }
    else if (((dx == x - 1 && dy == y + 1) || (dx == x - 1 && dy == y - 1)) && board[dx][dy] >= 'A' && board[dx][dy] <= 'Z') {
        return true;
    }
    else if (dx == x - 1 && dy == y && board[dx][dy] == '.') {
        return true;
    }
    return false;
}

bool pawnvalidmove2(char** board, int x, int y, int dx, int dy) {
    if (x == 1) {
        if ((dx == x + 2 || dx == x + 1) && y == dy && board[x + 1][y] == '.' && board[dx][dy] == '.')
            return true;
    }
    else if (((dx == x + 1 && dy == y - 1) || (dx == x + 1 && dy == y + 1)) && board[dx][dy] >= 'a' && board[dx][dy] <= 'z') {
        return true;
    }
    else if (dx == x + 1 && dy == y && board[dx][dy] == '.') {
        return true;
    }
    return false;
}
void promotePawn(char** board, int dx, int dy, int turn) {
    char choice;
    cout << "Promote your pawn to (q: Queen, r: Rook, b: Bishop, h: Knight): ";
    cin >> choice;

    if (turn == 1) board[dx][dy] = (choice >= 'A' && choice <= 'Z') ? choice + 32 : choice;
    else board[dx][dy] = (choice >= 'a' && choice <= 'z') ? choice - 32 : choice;
}

bool rookvalidmove(char** board, int x, int y, int dx, int dy) {
    if (x == dx) {
        int start = y < dy ? y + 1 : dy + 1;
        int end = y > dy ? y : dy;
        for (int i = start; i < end; i++) {
            if (board[x][i] != '.')
                return false;
        }
        return true;
    }
    else if (y == dy) {
        int start = x < dx ? x + 1 : dx + 1;
        int end = x > dx ? x : dx;
        for (int i = start; i < end; i++) {
            if (board[i][y] != '.')
                return false;
        }
        return true;
    }
    return false;
}


bool knightvalidmove(char** board, int x, int y, int dx, int dy, bool isWhite) {
    if ((dx == x + 2 && (dy == y + 1 || dy == y - 1)) ||
        (dx == x - 2 && (dy == y + 1 || dy == y - 1)) ||
        (dy == y + 2 && (dx == x + 1 || dx == x - 1)) ||
        (dy == y - 2 && (dx == x + 1 || dx == x - 1))) {
        char dest = board[dx][dy];
        if (dest == '.' || (isWhite && dest >= 'a' && dest <= 'z') || (!isWhite && dest >= 'A' && dest <= 'Z')) {
            return true;
        }
    }
    return false;
}


bool bishopvalidmove(char** board, int x, int y, int dx, int dy) {
    if ((dx - x == dy - y) || (dx - x == y - dy)) {
        int xStep = (dx > x) ? 1 : -1;
        int yStep = (dy > y) ? 1 : -1;
        for (int i = x + xStep, j = y + yStep; i != dx; i += xStep, j += yStep) {
            if (board[i][j] != '.')
                return false;
        }
        return true;
    }
    return false;
}


bool queenvalidmove(char** board, int x, int y, int dx, int dy) {
    return rookvalidmove(board, x, y, dx, dy) || bishopvalidmove(board, x, y, dx, dy);
}


bool kingvalidmove(char** board, int x, int y, int dx, int dy, bool isWhite) {
    if ((dx - x >= -1 && dx - x <= 1) && (dy - y >= -1 && dy - y <= 1)) {
        char dest = board[dx][dy];
        if (dest == '.' || (isWhite && dest >= 'a' && dest <= 'z') || (!isWhite && dest >= 'A' && dest <= 'Z')) {
            return true;
        }
    }
    return false;
}



bool validmove(char** board, int x, int y, int dx, int dy, int turn) {
    if (dx < 0 || dy < 0 || dx >= rows || dy >= cols)
        return false;
    char piece = player(board, x, y);
    if (piece == 'p' && turn == 1)
        return pawnvalidmove1(board, x, y, dx, dy);
    else if (piece == 'P' && turn == 0)
        return pawnvalidmove2(board, x, y, dx, dy);
    else if (piece == 'r' && turn == 1 || piece == 'R' && turn == 0)
        return rookvalidmove(board, x, y, dx, dy);
    else if (piece == 'h' && turn == 1 || piece == 'H' && turn == 0)
        return knightvalidmove(board, x, y, dx, dy, turn == 0);
    else if (piece == 'b' && turn == 1 || piece == 'B' && turn == 0)
        return bishopvalidmove(board, x, y, dx, dy);
    else if (piece == 'q' && turn == 1 || piece == 'Q' && turn == 0)
        return queenvalidmove(board, x, y, dx, dy);
    else if (piece == 'k' && turn == 1 || piece == 'K' && turn == 0)
        return kingvalidmove(board, x, y, dx, dy, turn == 0);
    return false;
}

void placement(char** board, int dx, int dy, int x, int y) {
    char piece = board[x][y];
    board[x][y] = '.';
    board[dx][dy] = piece;
}

bool isUnderAttack(char** board, int kingX, int kingY, int turn) {
    char opponentPawn = (turn == 1) ? 'P' : 'p';
    char opponentRook = (turn == 1) ? 'R' : 'r';
    char opponentKnight = (turn == 1) ? 'H' : 'h';
    char opponentBishop = (turn == 1) ? 'B' : 'b';
    char opponentQueen = (turn == 1) ? 'Q' : 'q';
    char opponentKing = (turn == 1) ? 'K' : 'k';

    if (turn == 1) {
        if ((kingX - 1 >= 0 && kingY - 1 >= 0 && board[kingX - 1][kingY - 1] == opponentPawn) ||
            (kingX - 1 >= 0 && kingY + 1 < cols && board[kingX - 1][kingY + 1] == opponentPawn))
            return true;
    }
    else {
        if ((kingX + 1 < rows && kingY - 1 >= 0 && board[kingX + 1][kingY - 1] == opponentPawn) ||
            (kingX + 1 < rows && kingY + 1 < cols && board[kingX + 1][kingY + 1] == opponentPawn))
            return true;
    }

    for (int i = 1; kingX + i < rows; i++) {
        if (board[kingX + i][kingY] != '.') {
            if (board[kingX + i][kingY] == opponentRook || board[kingX + i][kingY] == opponentQueen)
                return true;
            break;
        }
    }
    for (int i = 1; kingX - i >= 0; i++) {
        if (board[kingX - i][kingY] != '.') {
            if (board[kingX - i][kingY] == opponentRook || board[kingX - i][kingY] == opponentQueen)
                return true;
            break;
        }
    }
    for (int i = 1; kingY + i < cols; i++) {
        if (board[kingX][kingY + i] != '.') {
            if (board[kingX][kingY + i] == opponentRook || board[kingX][kingY + i] == opponentQueen)
                return true;
            break;
        }
    }
    for (int i = 1; kingY - i >= 0; i++) {
        if (board[kingX][kingY - i] != '.') {
            if (board[kingX][kingY - i] == opponentRook || board[kingX][kingY - i] == opponentQueen)
                return true;
            break;
        }
    }

    for (int i = 1; kingX + i < rows && kingY + i < cols; i++) {
        if (board[kingX + i][kingY + i] != '.') {
            if (board[kingX + i][kingY + i] == opponentBishop || board[kingX + i][kingY + i] == opponentQueen)
                return true;
            break;
        }
    }
    for (int i = 1; kingX + i < rows && kingY - i >= 0; i++) {
        if (board[kingX + i][kingY - i] != '.') {
            if (board[kingX + i][kingY - i] == opponentBishop || board[kingX + i][kingY - i] == opponentQueen)
                return true;
            break;
        }
    }
    for (int i = 1; kingX - i >= 0 && kingY + i < cols; i++) {
        if (board[kingX - i][kingY + i] != '.') {
            if (board[kingX - i][kingY + i] == opponentBishop || board[kingX - i][kingY + i] == opponentQueen)
                return true;
            break;
        }
    }
    for (int i = 1; kingX - i >= 0 && kingY - i >= 0; i++) {
        if (board[kingX - i][kingY - i] != '.') {
            if (board[kingX - i][kingY - i] == opponentBishop || board[kingX - i][kingY - i] == opponentQueen)
                return true;
            break;
        }
    }

    int knightMoves[8][2] = { {2, 1}, {2, -1}, {-2, 1}, {-2, -1}, {1, 2}, {1, -2}, {-1, 2}, {-1, -2} };
    for (auto& move : knightMoves) {
        int newX = kingX + move[0];
        int newY = kingY + move[1];
        if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && board[newX][newY] == opponentKnight)
            return true;
    }

    for (int dx = -1; dx <= 1; dx++) {
        for (int dy = -1; dy <= 1; dy++) {
            if (dx == 0 && dy == 0)
                continue;
            int newX = kingX + dx;
            int newY = kingY + dy;
            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && board[newX][newY] == opponentKing)
                return true;
        }
    }

    return false;
}

int main() {
    char** board = createBoard();
    boardInitialization(board);
    int turn = 1;
    bool gameRunning = true;
    int x, y, dx, dy;

    cout << "Welcome to Chess!" << endl;
    printBoard(board);

    while (gameRunning) {
        cout << "Player " << turn << "'s turn." << endl;


        source(x, y, turn);


        char piece = player(board, x, y);
        if ((turn == 1 && (piece < 'a' || piece > 'z')) || (turn == 0 && (piece < 'A' || piece > 'Z'))) {
            cout << "Invalid piece. Please select your own piece!" << endl;
            continue;
        }


        destination(dx, dy, turn);

        if (!validmove(board, x, y, dx, dy, turn)) {
            cout << "Invalid move! Try again." << endl;
            continue;
        }

        saveBoardState(board, "previousmove.txt");

        placement(board, dx, dy, x, y);

        if ((piece == 'p' && dx == 0) || (piece == 'P' && dx == rows - 1)) {
            promotePawn(board, dx, dy, turn);
        }


        int kingX = -1, kingY = -1;
        char king = (turn % 2 == 1) ? 'k' : 'K';
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (board[i][j] == king) {
                    kingX = i;
                    kingY = j;
                    break;
                }
            }
        }
        if (isUnderAttack(board, kingX, kingY, turn % 2)) {
            cout << "Checkmate! Player " << (turn % 2 == 1 ? "2" : "1") << " wins!" << endl;
            break;
        }

        printBoard(board);

        char choice;
        cout << "Do you want to undo the move? (y/n): ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y') {
            if (!undoMove(board)) {
                cout << "Undo failed." << endl;
            }
            else {
                cout << "Move undone." << endl;
                printBoard(board);
                continue;
            }
        }

        turn = 1 - turn;
    }

    deleteBoard(board);
    cout << "Thanks for playing!" << endl;
    return 0;
}

