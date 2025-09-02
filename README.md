# Five-in-a-Row Game

A complete five-in-a-row (Gomoku) game developed with C++ and EasyX Graphics Library, supporting multiple game modes and online multiplayer functionality.

## Game Features
- **Player vs AI** - Challenge AI opponents
  - Easy Mode: Basic AI algorithm
  - Hard Mode: Intelligent AI algorithm with undo functionality
- **Local Player vs Player** - Two-player game on the same computer
- **Online Multiplayer** - Support for LAN online battles
  - Create Room Mode
  - Join Room Mode


## Technical Implementation

### Development Environment
- **Programming Language**: C++
- **Graphics Library**: EasyX Graphics Library
- **Network Library**: WinSock2
- **Compiler**: C++ compiler supporting Windows platform

### Core Algorithms
- **Win/Lose Detection**: Eight-directional consecutive piece detection algorithm
- **AI Algorithm**: Intelligent piece placement based on scoring system
- **Network Communication**: TCP Socket communication protocol


## Installation and Running

### Requirements
- Windows operating system
- C++ compiler (such as Visual Studio, Dev-C++, etc.)
- EasyX graphics library

### Compilation Steps
1. Install EasyX graphics library
2. Open `gobang.cpp` with a C++-supporting IDE
3. Compile the project
4. Run the generated exe file

### Direct Execution
If you already have the compiled exe file, simply double-click `gobang.exe` to run the game.


## Game Rules
- Black pieces go first, white pieces second
- On a 15×15 board, the first to connect five pieces wins
- Supports horizontal, vertical, and diagonal connections

## Online Multiplayer Guide

### Creating a Room
1. Select "Online Multiplayer" → "Create Room"
2. Wait for other players to join
3. Start the game

### Joining a Room
1. Select "Online Multiplayer" → "Join Room"
2. Enter the host's IP address
3. Start the game after successful connection

### Network Requirements
- LAN environment
- Port 8888 open
- Stable network connection


**Enjoy the fun of Five-in-a-Row!** 🎯✨
