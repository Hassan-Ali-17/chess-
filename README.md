```
 ██████╗██╗  ██╗███████╗███████╗███████╗
██╔════╝██║  ██║██╔════╝██╔════╝██╔════╝
██║     ███████║█████╗  ███████╗███████╗
██║     ██╔══██║██╔══╝  ╚════██║╚════██║
╚██████╗██║  ██║███████╗███████║███████║
 ╚═════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝

 ██████╗         ███████╗██████╗ ██╗████████╗██╗ ██████╗ ███╗   ██╗
██╔════╝         ██╔════╝██╔══██╗██║╚══██╔══╝██║██╔═══██╗████╗  ██║
██║              █████╗  ██║  ██║██║   ██║   ██║██║   ██║██╔██╗ ██║
██║              ██╔══╝  ██║  ██║██║   ██║   ██║██║   ██║██║╚██╗██║
╚██████╗         ███████╗██████╔╝██║   ██║   ██║╚██████╔╝██║ ╚████║
 ╚═════╝         ╚══════╝╚═════╝ ╚═╝   ╚═╝   ╚═╝ ╚═════╝ ╚═╝  ╚═══╝
```

<div align="center">

**A fully functional console-based Chess game in C++ — available in two flavors: Pointer/Function-based and full OOP.**

[![Language](https://img.shields.io/badge/Language-C%2B%2B17-blue?style=flat-square&logo=cplusplus)](https://isocpp.org/)
[![Type](https://img.shields.io/badge/Type-Console%20App-green?style=flat-square)]()
[![Versions](https://img.shields.io/badge/Versions-PF%20%7C%20OOP-purple?style=flat-square)]()
[![Players](https://img.shields.io/badge/Players-2%20Local-orange?style=flat-square)]()

</div>

---

## 📋 Table of Contents

- [Overview](#-overview)
- [Two Versions](#-two-versions)
- [Features](#-features)
- [Chess Rules Implemented](#-chess-rules-implemented)
- [OOP Design](#-oop-design)
- [Board Preview](#-board-preview)
- [How to Run](#-how-to-run)
- [How to Play](#-how-to-play)
- [File Structure](#-file-structure)
- [Contributors](#-contributors)

---

## ♟️ Overview

This repository contains a **fully playable Chess game** built in C++ as a semester project. The game runs entirely in the terminal, supports two human players, and enforces all standard chess rules — including the tricky special moves most implementations skip.

The project comes in **two separate implementations** to demonstrate different C++ programming paradigms.

---

## 🔀 Two Versions

| | PF Version | OOP Version |
|---|---|---|
| **Paradigm** | Procedural / Function-based | Object-Oriented |
| **Memory** | Pointers & double pointers | Classes & dynamic allocation |
| **Board** | `char**` 2D pointer array | `Piece*` object array |
| **Focus** | Memory management, raw pointers | Inheritance, polymorphism |
| **Special Moves** | ✅ | ✅ including castling & en passant |

---

## ✨ Features

```
┌──────────────────────────────────────────────────────┐
│                  GAME FEATURES                       │
├──────────────────────────────────────────────────────┤
│  ♟️  Full chess rules — both versions                │
│  🏰  Castling (kingside & queenside)                 │
│  👻  En Passant (that sneaky pawn capture)           │
│  👑  Pawn Promotion                                  │
│  ✅  Check & Checkmate detection                     │
│  🚫  Illegal move prevention                         │
│  🎮  Two-player local multiplayer                    │
│  🖥️  Clean text-based board display                  │
│  🔄  Turn-based gameplay with move validation        │
└──────────────────────────────────────────────────────┘
```

---

## ♟️ Chess Rules Implemented

### Standard Movement

All 6 piece types move exactly as per official chess rules:

| Piece | Symbol | Movement |
|---|---|---|
| King | `K` | One square any direction |
| Queen | `Q` | Any direction, any distance |
| Rook | `R` | Horizontal / Vertical |
| Bishop | `B` | Diagonal only |
| Knight | `N` | L-shape, jumps over pieces |
| Pawn | `P` | Forward 1 (or 2 from start), captures diagonally |

### Special Moves

**🏰 Castling**
```
Before:   R . . . K . . R
After:    . . K R . . . .   (kingside)
          . . . . . R K .   (queenside)
```
King and rook swap positions in one move. Only valid when:
- Neither piece has moved yet
- No pieces standing between them
- King is not in check, and doesn't pass through or land on a checked square

**👻 En Passant**
```
  White pawn on e5, Black plays d7 → d5 (two-square advance)
  White CAN capture: e5 × d6  (landing on d6, removing the pawn on d5)
  ⏳ Must be played immediately — the window lasts exactly ONE turn!
```
When a pawn advances two squares from its starting rank and lands beside an enemy pawn, the enemy pawn may capture it diagonally as though it had only moved one square. Miss the turn — lose the chance forever.

**👑 Pawn Promotion**

When a pawn reaches the opposite end of the board (rank 8 for White, rank 1 for Black), the player chooses to promote it to a Queen, Rook, Bishop, or Knight.

---

## 🧠 OOP Design

The OOP version demonstrates all core OOP principles:

### Inheritance Hierarchy
```
         Piece  (abstract base class)
        /  |   \    \      \      \
      King Queen Rook Bishop Knight Pawn
```
Each piece inherits common attributes (`color`, `position`, `hasMoved`) and overrides the virtual `isValidMove()` method with its own movement logic.

### Polymorphism
```cpp
Piece* board[8][8];

// Calls the correct isValidMove() for whatever piece sits on that square
if (board[row][col]->isValidMove(destination)) {
    makeMove();
}
```
The game loop handles every piece type through one uniform interface — no giant `if/else` chains checking piece types.

### Encapsulation
Each piece class keeps its data `private` and exposes only what other classes need. The board doesn't know *how* a knight moves — it just asks the knight.

### Abstraction
`Piece` declares a **pure virtual** `isValidMove()`, forcing every subclass to implement its own rules. The rest of the system never needs to know which piece it's dealing with.

### Composition
```
  Game
   ├── Board          (owns the 8×8 Piece* grid)
   ├── Player × 2     (turn tracking, captured pieces)
   └── MoveHistory    (stores last move — required for en passant & castling checks)
```

---

## 🖥️ Board Preview

```
  +---+---+---+---+---+---+---+---+
8 | r | n | b | q | k | b | n | r |
  +---+---+---+---+---+---+---+---+
7 | p | p | p | p | p | p | p | p |
  +---+---+---+---+---+---+---+---+
6 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
5 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
4 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
3 |   |   |   |   |   |   |   |   |
  +---+---+---+---+---+---+---+---+
2 | P | P | P | P | P | P | P | P |
  +---+---+---+---+---+---+---+---+
1 | R | N | B | Q | K | B | N | R |
  +---+---+---+---+---+---+---+---+
    a   b   c   d   e   f   g   h

  Uppercase = White      Lowercase = Black
```

---

## 🚀 How to Run

### Prerequisites
- `g++` with C++17 support

### PF Version
```bash
cd PF_version
g++ -std=c++17 *.cpp -o chess_pf
./chess_pf
```

### OOP Version
```bash
cd OOP_version
g++ -std=c++17 *.cpp -o chess_oop
./chess_oop
```

**Windows:**
```bash
g++ -std=c++17 *.cpp -o chess.exe
chess.exe
```

---

## 🎮 How to Play

```
  ♟ White's turn
  Enter move (e.g. e2 e4): _
```

- Type **source square** then **destination square** separated by a space
- The board redraws after every valid move
- Invalid or illegal moves are rejected — try again
- Game ends on **Checkmate** or **Stalemate**

**Special move inputs:**
| Move | Input example |
|---|---|
| Normal move | `e2 e4` |
| Capture | `d4 e5` |
| Castling (kingside) | `e1 g1` — just move the king two squares |
| En Passant | `e5 d6` — capture diagonally, detected automatically |
| Pawn Promotion | Move pawn to rank 8, then choose piece when prompted |

---

## 📁 File Structure

```
chess-/
│
├── PF_version/
│   ├── main.cpp          # Entry point
│   ├── board.cpp/h       # Board using char** double pointer
│   ├── moves.cpp/h       # All movement logic as functions
│   ├── display.cpp/h     # Terminal board rendering
│   └── utils.cpp/h       # Input parsing, helper functions
│
├── OOP_version/
│   ├── main.cpp          # Entry point
│   ├── Piece.h           # Abstract base class with pure virtual isValidMove()
│   ├── King.cpp/h        # King movement + castling logic
│   ├── Queen.cpp/h
│   ├── Rook.cpp/h
│   ├── Bishop.cpp/h
│   ├── Knight.cpp/h
│   ├── Pawn.cpp/h        # Pawn movement + en passant + promotion
│   ├── Board.cpp/h       # 8×8 Piece* array, move execution
│   ├── Game.cpp/h        # Game loop, check/checkmate detection
│   ├── Player.cpp/h      # Player state, turn management
│   └── MoveHistory.cpp/h # Tracks last move for special move validation
│
└── README.md
```

---

## 👥 Contributors

| Name | GitHub |
|---|---|
| Hassan Ali | [@Hassan-Ali-17](https://github.com/Hassan-Ali-17) |

---

<div align="center">

*Built with C++ · Semester Project · Console Chess · Two Implementations*

♙ ♘ ♗ ♖ ♕ ♔ ♚ ♛ ♜ ♝ ♞ ♟

</div>
