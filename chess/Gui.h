//#ifndef GUI_H
//#define GUI_H
//
//#include <windows.h>
//#include <iostream>
//
//class GUI {
//private:
//    HANDLE hConsole;
//
//public:
//    // Color codes
//    static const int BLACK = 0;
//    static const int DARK_BLUE = 1;
//    static const int DARK_GREEN = 2;
//    static const int DARK_CYAN = 3;
//    static const int DARK_RED = 4;
//    static const int DARK_MAGENTA = 5;
//    static const int DARK_YELLOW = 6;
//    static const int LIGHT_GRAY = 7;
//    static const int DARK_GRAY = 8;
//    static const int BLUE = 9;
//    static const int GREEN = 10;
//    static const int CYAN = 11;
//    static const int RED = 12;
//    static const int MAGENTA = 13;
//    static const int YELLOW = 14;
//    static const int WHITE = 15;
//
//    GUI() {
//        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//    }
//
//    void setColor(int textColor, int bgColor = BLACK) {
//        SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
//    }
//
//    void resetColor() {
//        setColor(WHITE, BLACK);
//    }
//
//    void clearScreen() {
//        system("cls");
//    }
//
//    void setCursorPosition(int x, int y) {
//        COORD coord;
//        coord.X = x;
//        coord.Y = y;
//        SetConsoleCursorPosition(hConsole, coord);
//    }
//
//    void printColoredText(const std::string& text, int textColor, int bgColor = BLACK) {
//        setColor(textColor, bgColor);
//        std::cout << text;
//        resetColor();
//    }
//
//    void drawBox(int x, int y, int width, int height, int color) {
//        setColor(color);
//
//        // Top border
//        setCursorPosition(x, y);
//        std::cout << char(201); // ╔
//        for (int i = 0; i < width - 2; i++) std::cout << char(205); // ═
//        std::cout << char(187); // ╗
//
//        // Side borders
//        for (int i = 1; i < height - 1; i++) {
//            setCursorPosition(x, y + i);
//            std::cout << char(186); // ║
//            setCursorPosition(x + width - 1, y + i);
//            std::cout << char(186); // ║
//        }
//
//        // Bottom border
//        setCursorPosition(x, y + height - 1);
//        std::cout << char(200); // ╚
//        for (int i = 0; i < width - 2; i++) std::cout << char(205); // ═
//        std::cout << char(188); // ╝
//
//        resetColor();
//    }
//
//    void printTitle(const std::string& title, int color) {
//        clearScreen();
//        setColor(color);
//        std::cout << "\n";
//        std::cout << "  ╔═══════════════════════════════════════╗\n";
//        std::cout << "  ║                                       ║\n";
//        std::cout << "  ║         " << title;
//        for (int i = title.length(); i < 28; i++) std::cout << " ";
//        std::cout << "  ║\n";
//        std::cout << "  ║                                       ║\n";
//        std::cout << "  ╚═══════════════════════════════════════╝\n\n";
//        resetColor();
//    }
//};
//
//#endif


#ifndef GUI_H
#define GUI_H

#include <windows.h>
#include <iostream>

class GUI {
private:
    HANDLE hConsole;

public:
    static const int BLACK = 0;
    static const int DARK_BLUE = 1;
    static const int DARK_GREEN = 2;
    static const int DARK_CYAN = 3;
    static const int DARK_RED = 4;
    static const int DARK_MAGENTA = 5;
    static const int DARK_YELLOW = 6;
    static const int LIGHT_GRAY = 7;
    static const int DARK_GRAY = 8;
    static const int BLUE = 9;
    static const int GREEN = 10;
    static const int CYAN = 11;
    static const int RED = 12;
    static const int MAGENTA = 13;
    static const int YELLOW = 14;
    static const int WHITE = 15;

    GUI() {
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    }

    void setColor(int textColor, int bgColor = BLACK) {
        SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
    }

    void resetColor() {
        setColor(WHITE, BLACK);
    }

    void clearScreen() {
        system("cls");
    }

    void setCursorPosition(int x, int y) {
        COORD coord;
        coord.X = x;
        coord.Y = y;
        SetConsoleCursorPosition(hConsole, coord);
    }

    bool getMouseClick(int& x, int& y) {
        HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode;
        GetConsoleMode(hInput, &mode);
        SetConsoleMode(hInput, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);

        INPUT_RECORD inputRecord;
        DWORD events;

        while (true) {
            ReadConsoleInput(hInput, &inputRecord, 1, &events);

            if (inputRecord.EventType == MOUSE_EVENT) {
                if (inputRecord.Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
                    int mouseX = inputRecord.Event.MouseEvent.dwMousePosition.X;
                    int mouseY = inputRecord.Event.MouseEvent.dwMousePosition.Y;
                    if (mouseY >= 8 && mouseY <= 23) {
                        int boardY = (mouseY - 8) / 2;
                        if (mouseX >= 5 && mouseX <= 36) {
                            int boardX = (mouseX - 5) / 4;
                            if (boardX >= 0 && boardX < 8 && boardY >= 0 && boardY < 8) {
                                x = boardY;
                                y = boardX;
                                SetConsoleMode(hInput, mode);
                                return true;
                            }
                        }
                    }
                }
            }

            if (inputRecord.EventType == KEY_EVENT && inputRecord.Event.KeyEvent.bKeyDown) {
                if (inputRecord.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE) {
                    SetConsoleMode(hInput, mode);
                    return false;
                }
            }
        }
    }

    void printColoredText(const std::string& text, int textColor, int bgColor = BLACK) {
        setColor(textColor, bgColor);
        std::cout << text;
        resetColor();
    }

    void drawBox(int x, int y, int width, int height, int color) {
        setColor(color);
        setCursorPosition(x, y);
        std::cout << char(201); 
        for (int i = 0; i < width - 2; i++) std::cout << char(205); 
        std::cout << char(187); 

        for (int i = 1; i < height - 1; i++) {
            setCursorPosition(x, y + i);
            std::cout << char(186); 
            setCursorPosition(x + width - 1, y + i);
            std::cout << char(186); 
        }

        setCursorPosition(x, y + height - 1);
        std::cout << char(200); 
        for (int i = 0; i < width - 2; i++) std::cout << char(205); 
        std::cout << char(188); 

        resetColor();
    }

    void printTitle(const std::string& title, int color) {
        clearScreen();
        setColor(color);
        std::cout << "\n";
        std::cout << "  ╔═══════════════════════════════════════╗\n";
        std::cout << "  ║                                       ║\n";
        std::cout << "  ║         " << title;
        for (int i = title.length(); i < 28; i++) std::cout << " ";
        std::cout << "  ║\n";
        std::cout << "  ║                                       ║\n";
        std::cout << "  ╚═══════════════════════════════════════╝\n\n";
        resetColor();
    }
};

#endif