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
     1. Install [MSYS2](https://www.msys2.org/): follow the official guide to download and run the installer.
     2. Open the MSYS2 MSYS terminal and run:
        ```bash
        pacman -Syu          # update package database
        ```
        ```bash
        pacman -S mingw-w64-x86_64-gcc
        ```
   - **macOS:**
        Open Terminal and install Xcode command line tools:
        ```bash
        xcode-select --install
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
   - **Linux:** part of `build-essential` on Ubuntu/Debian

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

Run the game via the engine’s play command:

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

- **Download:** Download the SDK from [https://www.sfml-dev.org](https://www.sfml-dev.org) and extract.
- **Install via package manager:**
   - **Windows (MSYS2):**
       ```bash
       pacman -S mingw-w64-x86_64-sfml
       ```
   - **macOS:**
       ```bash
       brew install sfml
       ```
   - **Ubuntu/Debian:**
       ```bash
       sudo apt-get update
       sudo apt-get install libsfml-dev
       ```

**Linking SFML in your Makefile** 
todo

Adjust include/library paths if SFML is installed elsewhere.

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
