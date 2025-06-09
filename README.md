# Undertale Muffet Game

A fan-made recreation of the iconic Muffet boss battle from *Undertale*. This game is built using **\[C++/SFML]** and aims to recreate a time based bullet hell version of the boss fight.

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

1. **Clone the repository**

   ```bash
   git clone https://github.com/robat28/Undertale_Muffet_Game.git
   cd Undertale_Muffet_Game
   ```
2. **Install dependencies**

   * If using **\[tool/package manager]**:

     ```bash
     [tool] install
     ```
   * Or manually install:

     * Library A vX.Y.Z
     * Library B vA.B.C
3. **Build the project**

   ```bash
   [build-command]
   ```

---

## Usage

Run the executable or start via the engine’s play command:

```bash
[run-command]
```

---

## Controls

| Action          | Default Key |
| --------------- | ----------- |
| Move            | W/A/S/D     |
| or              | Arrow keys  |
| Select          | W / S       |
| Confirm         | Enter       |

---

## Dependencies

This project uses **SFML (Simple and Fast Multimedia Library)** for graphics, window management, and audio. To keep the repo lean, **we do not include SFML’s source or binaries** directly. Instead, choose one of the following approaches:

### 1. Install via your system/package manager

* **Windows:** Download the SDK from [https://www.sfml-dev.org](https://www.sfml-dev.org) and extract; set `SFML_ROOT` to the SDK path.
* **macOS:** `brew install sfml`
* **Ubuntu/Debian:** `sudo apt-get install libsfml-dev`

Then CMake will automatically locate it (assuming `SFML_ROOT` or standard search paths).

**For Makefile users**, here’s an example snippet after installing via your OS package manager:

```makefile
# Example Makefile for Linux/macOS
CXX = g++
CXXFLAGS = -std=c++17 -I/usr/local/include
LDFLAGS = -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SRC = $(wildcard src/*.cpp)
OBJ = $(SRC:.cpp=.o)
TARGET = MuffetGame

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)
```

Adjust include/library paths if SFML is installed elsewhere.

### 2. Add SFML as a Git submodule

```bash
git submodule add https://github.com/SFML/SFML external/SFML
git submodule update --init --recursive
```

And in your `CMakeLists.txt`:

```cmake
add_subdirectory(external/SFML)
find_package(SFML 2.5 COMPONENTS graphics window system audio REQUIRED)

add_executable(${PROJECT_NAME} src/main.cpp ...)
# link your target against SFML
target_link_libraries(${PROJECT_NAME}
    PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
```

### 3. Use a package manager (vcpkg, Conan, etc.)

For example with **vcpkg**:

```bash
vcpkg install sfml:x64-windows
# then integrate:
cmake -B build -DCMAKE_TOOLCHAIN_FILE=/path/to/vcpkg.cmake
```

By using these methods, **you avoid bloating the repo** and keep SFML versioning flexible.

---

## Contributing

Contributions are welcome! To contribute:

1. Fork the repo
2. Create a new branch (`git checkout -b feature/your-feature`)
3. Make your changes and commit (`git commit -m "Add awesome feature"`)
4. Push to your branch (`git push origin feature/your-feature`)
5. Open a Pull Request describing your changes

Please follow the [code style guide](docs/CODE_STYLE.md) and run all tests before submitting.

---

## License

This project is licensed under the [MIT License](LICENSE).

---

## Contact

Maintainer: **robat28**
GitHub: [github.com/robat28](https://github.com/robat28)
