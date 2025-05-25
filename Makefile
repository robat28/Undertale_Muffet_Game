# Chose Compiler (Default clang++)
CXX = clang++

# All source files
SRC = src/main.cpp src/Game.cpp src/Player.cpp src/Enemy.cpp src/Playfield.cpp src/GUI.cpp src/Spawner.cpp src/Menu.cpp src/DefeatMenu.cpp src/GameScreen.cpp

# All links to sfml files
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Standard c++ flags (Default c++17)
FLAGS = -o bin/main -I./include -stdlib=libc++ -std=c++17

main: $(SRC) bin
  $(CXX) $(SRC) $(LFLAGS) $(FLAGS) 

bin: 
	mkdir -p bin

clean:
	rm -r bin 