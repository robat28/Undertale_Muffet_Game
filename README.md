# Undertale Muffet Game

A fan-made recreation of the iconic Muffet boss battle from *Undertale*. This game is built using **\[C++/SFML3]** and aims to recreate a time based bullet hell version of the boss fight.

---

## Table of Contents

* [Installation](#installation)
* [Usage](#usage)
* [Controls](#controls)
* [Dependencies](#dependencies)
* [Contributing](#contributing)
* [License](#license)
* [Contact](#contact)

---

## Installation

If you’re new to C++, follow these steps in order:

1. **Install a C++ compiler**
   - **Windows:**
     1. Install MSYS2 from [https://www.msys2.org/](https://www.msys2.org/) and follow the official guide to download and run the installer.
     2. Open the MSYS2 MSYS terminal and run: 
        ```bash
        pacman -Syu         
        ```
        ```bash
        pacman -S mingw-w64-x86_64-gcc
        ```
   - **macOS:**
        Open Terminal and install Xcode command line tools:
        ```bash
        xcode-select --install
        ```
   - **Linux (Arch):**
        ```bash
        sudo pacman -Syu
        ```
        ```bash
        sudo pacman -S base-devel
        ```
   - **Linux (Ubuntu/Debian):**
        ```bash
        sudo apt-get update
        ```
        ```bash
        sudo apt-get install build-essential
        ```

2. **Install Make** (if not already installed)
   - **Windows (MSYS2):** included with MSYS2 above
   - **macOS:** included with Xcode tools
   - **Linux:** part of `build-essential` on Ubuntu/Debian and `base-devel` on Arch

3. **Clone this repository**
      ```bash
      git clone https://github.com/robat28/Undertale_Muffet_Game.git
      ```
      ```bash
      cd Undertale_Muffet_Game
      ```
   
4. **Install SFML** (see Dependencies)

5. **Build the game**
      ```bash
      make
      ```

---

## Usage

Run the game via the play command:
   ```bash
   bin/Muffet_Game
   ```

---

## Controls

| Action          | Default Key |
| --------------- | ----------- |
| Move            | W/A/S/D     |
|                 | Arrow keys  |
| Select          | W / S       |
| Confirm         | Enter       |

---

## Dependencies

This project uses **SFML3 (Simple and Fast Multimedia Library)** for graphics, window management, and audio. To keep the repo lean, **we do not include SFML’s source or binaries** directly.

### Install SFML 3.0.1

*  **Download:** Download the SDK from [https://www.sfml-dev.org](https://www.sfml-dev.org) and extract.
*  **Install via package manager:**
   - **Windows (MSYS2):**
      ```bash
      pacman -S mingw-w64-x86_64-sfml
      ```
   - **macOS:**
      ```bash
      brew install sfml
      ```
   - **Arch:**
      ```bash
      sudo pacman -Syu
      ```
      ```bash
      sudo pacman -S sfml
      ```
   - **Ubuntu/Debian:**
      ```bash
      sudo apt-get update
      ```
      ```bash
      sudo apt-get install libsfml-dev
      ```
   


### Linking SFML in your Makefile

* Adjust include/library paths and compiler if SFML is installed elsewhere or you are using another compiler.

* **Windows:** 
   - If you installed the SFML SDK, follow the instructions of the Makefile below. 
   - (Simply uncomment the given lines by removing the '#' and comment the default lines by writting a '#' in front of the line and add the path to your SFML library.)
   - If you installed SFML with MSYS2: Set `SFML_HOME=/mingw64`
```makefile
# Choose Compiler (Default g++)
CXX = g++

# If you installed the SDK, uncomment and set SFML_HOME to your SDK path:
#SFML_HOME = <Insert path to SDK here, e.g. C:/SFML/3.0.1>       <-- Remove '#' and insert path

# All source files
SRC = src/main.cpp src/Game.cpp src/Player.cpp src/Enemy.cpp src/Playfield.cpp src/GUI.cpp src/Spawner.cpp src/Menu.cpp src/DefeatMenu.cpp src/GameScreen.cpp src/ScoresScreen.cpp

# All links to SFML modules
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio # Default (cross-platform)       <-- Write '#' at beginning

# With SDK (uncomment to use SFML_HOME):
#LFLAGS = -L$(SFML_HOME)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio        <-- Remove '#'

# Standard C++ flags (Default C++17)
FLAGS = -o bin/Muffet_Game -I./include -std=c++17 # Default include path      <-- Write '#' at beginning

# With SDK (uncomment to use SFML_HOME):
#FLAGS = -o bin/Muffet_Game -I$(SFML_HOME)/include -I./include -std=c++17        <-- Remove '#'

...
```

* **macOS / Linux:**

   - If you installed SFML with a package manager, you don't need to change anything in the Makefile and you are ready to go on.

---

## Contributing

Contributions are welcome! To contribute:

1. Fork the repo
2. Create a new branch (`git checkout -b feature/your-feature`)
3. Make your changes and commit (`git commit -m "Add awesome feature"`)
4. Push to your branch (`git push origin feature/your-feature`)
5. Open a Pull Request describing your changes

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Contact

Maintainer: **robat28**
GitHub: [github.com/robat28](https://github.com/robat28)
