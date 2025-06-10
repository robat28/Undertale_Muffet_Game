# Choose Compiler (Default g++)
CXX = g++

# Windows users:
# Uncomment and set SFML_HOME to your SDK path:
# SFML_HOME = <Insert SDK path here>, e.g. C:/SFML

# All source files
SRC = src/main.cpp src/Game.cpp src/Player.cpp src/Enemy.cpp src/Playfield.cpp src/GUI.cpp src/Spawner.cpp src/Menu.cpp src/DefeatMenu.cpp src/GameScreen.cpp src/ScoresScreen.cpp

# All links to SFML modules
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio # Default (cross-platform)

# Windows (uncomment to use SFML_HOME):
# LFLAGS = -L$(SFML_HOME)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Standard C++ flags (Default C++17)
FLAGS = -o bin/Muffet_Game -I./include -std=c++17 # Default include path

# Windows (uncomment to use SFML_HOME):
# FLAGS = -o bin/Muffet_Game -I$(SFML_HOME)/include -std=c++17

main: $(SRC) bin
	$(CXX) $(SRC) $(LFLAGS) $(FLAGS)

bin:
	mkdir -p bin

clean:
	rm -r bin
