<div align="center">
  <img src="assets/icons/game_icon.png" alt="Sudoku Game" width="200" height="200">
  <h1>🎯 Sudoku Game</h1>
  <p><strong>A feature-rich Sudoku game built with C and Raylib</strong></p>
  
  [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
  [![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-blue.svg)](https://github.com/yourusername/Sudoku_Game)
  [![Language](https://img.shields.io/badge/Language-C-orange.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
  [![Graphics](https://img.shields.io/badge/Graphics-Raylib-green.svg)](https://www.raylib.com/)
</div>

---

## 📋 Table of Contents

- [🎮 Overview](#-overview)
- [✨ Features](#-features)
- [🚀 Getting Started](#-getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
  - [Building](#building)
  - [Running](#running)
- [🎯 How to Play](#-how-to-play)
- [🏗️ Project Structure](#️-project-structure)
- [🔧 Technical Details](#-technical-details)
- [📊 Game States](#-game-states)
- [💾 Data Management](#-data-management)
- [🎨 Customization](#-customization)
- [🤝 Contributing](#-contributing)
- [📄 License](#-license)
- [👤 Author](#-author)

---

## 🎮 Overview

**Sudoku Game** is a comprehensive, cross-platform Sudoku implementation built entirely in C using the Raylib graphics library. This project demonstrates advanced C programming concepts including object-oriented programming patterns, file I/O, data persistence, and real-time user input validation.

The game features a complete user authentication system, multiple difficulty levels, game state persistence, and an intuitive graphical interface that provides an engaging puzzle-solving experience.

---

## ✨ Features

### 🔐 **User Authentication System**
- **Sign Up**: Create new player accounts with validation
- **Log In**: Secure authentication for existing players
- **Player Management**: CSV-based player data storage
- **Input Validation**: Real-time validation for usernames and passwords

### 🎯 **Game Features**
- **Three Difficulty Levels**: Easy (20 cells removed), Medium (40 cells removed), Hard (60 cells removed)
- **Smart Puzzle Generation**: Uses backtracking algorithm for valid Sudoku generation
- **Real-time Validation**: Instant feedback on correct/incorrect moves
- **Game State Persistence**: Save and resume games at any time
- **Timer System**: Track solving time with pause/resume functionality
- **Mistake Tracking**: Monitor incorrect attempts

### 🎨 **User Interface**
- **Modern GUI**: Clean, intuitive interface built with Raylib
- **Responsive Design**: 600x600 window with scalable elements
- **Visual Feedback**: Color-coded cells and validation indicators
- **Loading Animations**: Smooth transitions with spinner effects
- **Tutorial System**: Built-in help and game rules

### 💾 **Data Management**
- **Player Profiles**: Persistent user accounts with statistics
- **Game Saves**: Individual save files per player
- **Solution Storage**: Pre-generated valid Sudoku solutions
- **CSV Integration**: Structured data storage and retrieval

---

## 🚀 Getting Started

### Prerequisites

Before building and running the Sudoku Game, ensure you have the following installed:

- **C Compiler**: GCC (GNU Compiler Collection)
- **Raylib Library**: Graphics library for rendering
- **Make**: Build automation tool
- **Git**: Version control (for cloning the repository)

#### Installing Raylib

**On Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install libraylib-dev
```

**On Windows (MSYS2/MinGW):**
```bash
pacman -S mingw-w64-x86_64-raylib
```

**On macOS:**
```bash
brew install raylib
```

### Installation

1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/Sudoku_Game.git
   cd Sudoku_Game
   ```

2. **Verify the project structure:**
   ```bash
   ls -la
   ```
   You should see directories: `assets/`, `data/`, `include/`, `source/`, `libraries/`

### Building

The project uses a cross-platform Makefile that automatically detects your operating system:

```bash
# Build the project
make

# Or build and run in one command
make run
```

**Build Output:**
- Linux: `build/main`
- Windows: `build/main.exe`

### Running

After building, you can run the game:

```bash
# Run the built executable
make run

# Or run directly
cd build && ./main
```

---

## 🎯 How to Play

### Getting Started
1. **Launch the game** and you'll see the sign-up screen
2. **Create an account** or **log in** if you already have one
3. **Choose your difficulty** from the main menu:
   - **Easy**: 20 cells removed (beginner-friendly)
   - **Medium**: 40 cells removed (intermediate)
   - **Hard**: 60 cells removed (expert level)

### Gameplay
1. **Click on empty cells** to select them
2. **Type numbers 1-9** to fill the selected cell
3. **Use the pause button** to save progress or return to menu
4. **Complete the puzzle** by filling all cells correctly

### Rules
- Each row must contain numbers 1-9 without repetition
- Each column must contain numbers 1-9 without repetition
- Each 3x3 sub-grid must contain numbers 1-9 without repetition
- The game validates your moves in real-time

---

## 🏗️ Project Structure

```
Sudoku_Game/
├── 📁 assets/                 # Game assets and resources
│   ├── 📁 fonts/             # Custom fonts
│   │   └── Adecion-Bold.ttf
│   ├── 📁 icons/             # Game icons
│   │   └── game_icon.png
│   └── 📁 images/            # UI images
│       ├── back.png
│       ├── pause.png
│       └── required.png
├── 📁 data/                  # Game data and persistence
│   ├── 📁 players/           # Player database
│   │   └── players.csv
│   ├── 📁 saves/             # Game save files
│   │   ├── ouss.txt
│   │   └── youne.txt
│   └── 📁 solution/          # Pre-generated solutions
│       └── solution.txt
├── 📁 include/               # Header files
│   ├── auth.h               # Authentication system
│   ├── config.h             # Game configuration
│   ├── difficulty.h         # Difficulty management
│   ├── menu.h               # Menu system
│   ├── play.h               # Game logic
│   ├── player.h             # Player management
│   ├── process.h            # Input processing
│   ├── raylib.h             # Graphics library
│   ├── render.h             # Rendering system
│   ├── result.h             # Results display
│   └── tutorial.h           # Tutorial system
├── 📁 libraries/            # External libraries
│   └── libraylib.a
├── 📁 source/               # Source code files
│   ├── auth.c
│   ├── config.c
│   ├── difficulty.c
│   ├── main.c
│   ├── menu.c
│   ├── play.c
│   ├── player.c
│   ├── process.c
│   ├── render.c
│   ├── result.c
│   └── tutorial.c
├── 📄 Makefile              # Build configuration
├── 📄 LICENSE               # MIT License
└── 📄 README.md             # This file
```

---

## 🔧 Technical Details

### Architecture

The game follows a **modular architecture** with clear separation of concerns:

- **State Management**: Finite state machine for game flow
- **Object-Oriented C**: Function pointers for method-like behavior
- **Data Persistence**: File-based storage for players and game states
- **Real-time Validation**: Immediate feedback on user input

### Key Components

#### 🎮 **Game Engine**
- **Main Loop**: Raylib-based rendering and input handling
- **State Machine**: 9 distinct game states (SIGN_UP, LOG_IN, MAIN_MENU, etc.)
- **Timer System**: High-precision timing for game duration

#### 🧩 **Sudoku Logic**
- **Backtracking Algorithm**: Generates valid Sudoku puzzles
- **Validation Engine**: Real-time move validation
- **Difficulty Scaling**: Configurable cell removal based on difficulty

#### 👤 **Player System**
- **Authentication**: Secure login/signup with validation
- **Profile Management**: Persistent player data
- **Save System**: Individual game state persistence

### Performance Features

- **Memory Management**: Proper allocation and deallocation
- **Efficient Rendering**: Optimized drawing calls
- **Fast Validation**: O(1) move validation algorithms
- **Cross-platform**: Works on Linux, Windows, and macOS

---

## 📊 Game States

The game implements a comprehensive state machine:

| State | Description | Features |
|-------|-------------|----------|
| `SIGN_UP` | User registration | Input validation, unique username check |
| `LOG_IN` | User authentication | Credential verification, error handling |
| `MAIN_MENU` | Main game menu | Navigation, player info display |
| `MODE_MENU` | Difficulty selection | Three difficulty levels |
| `TUTORIAL` | Game tutorial | Interactive help system |
| `PLAYING` | Active gameplay | Sudoku solving, real-time validation |
| `LOADING` | Transition state | Animated spinner, smooth transitions |
| `RESULT` | Game completion | Statistics, performance metrics |
| `EXIT` | Application exit | Cleanup, resource deallocation |

---

## 💾 Data Management

### Player Data (`data/players/players.csv`)
```csv
Name,Password
youne,sbai_test
ouss,arif_test
taha,ammour_test
```

### Game Saves (`data/saves/`)
- Individual save files per player
- Contains: grid state, difficulty, timer, mistakes
- Automatic cleanup on game completion

### Solutions (`data/solution/`)
- Pre-generated valid Sudoku solutions
- Used for puzzle generation and validation
- Ensures solvable puzzles at all difficulty levels

---

## 🎨 Customization

### Visual Customization
- **Window Size**: Modify `WINDOW_WIDTH` and `WINDOW_HEIGHT` in `config.h`
- **Cell Size**: Adjust `CELL_SIZE` for different grid dimensions
- **Colors**: Customize color schemes in rendering functions
- **Fonts**: Replace fonts in `assets/fonts/` directory

### Gameplay Customization
- **Difficulty Levels**: Modify cell removal counts in `config.h`
- **Validation Rules**: Customize input validation in `player.h`
- **Timer Behavior**: Adjust timing logic in game state handlers

### Build Customization
- **Compiler Flags**: Modify `CFLAGS` in `Makefile`
- **Platform Support**: Add new platforms in `Makefile`
- **Dependencies**: Update library paths as needed

---

## 🤝 Contributing

We welcome contributions to improve the Sudoku Game! Here's how you can help:

### 🐛 **Bug Reports**
- Use the issue tracker to report bugs
- Include steps to reproduce the issue
- Provide system information (OS, compiler version)

### 💡 **Feature Requests**
- Suggest new features or improvements
- Discuss implementation approaches
- Consider backward compatibility

### 🔧 **Code Contributions**
1. **Fork the repository**
2. **Create a feature branch**: `git checkout -b feature/amazing-feature`
3. **Commit your changes**: `git commit -m 'Add amazing feature'`
4. **Push to the branch**: `git push origin feature/amazing-feature`
5. **Open a Pull Request**

### 📋 **Coding Standards**
- Follow existing code style and naming conventions
- Add comments for complex logic
- Ensure cross-platform compatibility
- Test on multiple operating systems

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

---

## 👤 Author

**Youness SBAI** - [GitHub Profile](https://github.com/SBAI-Youness)

---

<div align="center">
  <p><strong>⭐ Star this repository if you found it helpful!</strong></p>
  <p>Made with ❤️ by SBAI</p>
</div>
