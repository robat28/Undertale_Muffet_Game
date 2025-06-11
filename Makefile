# Choose Compiler (Default g++)
CXX = g++

# If you installed the SDK, uncomment and set SFML_HOME to your SDK path:
#SFML_HOME = <Insert path to SDK here, e.g. C:/SFML/3.0.1>

# All source files
SRC = src/main.cpp src/Game.cpp src/Player.cpp src/Enemy.cpp src/Playfield.cpp src/GUI.cpp src/Spawner.cpp src/Menu.cpp src/DefeatMenu.cpp src/GameScreen.cpp src/ScoresScreen.cpp

# All links to SFML modules
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio # Default (cross-platform)

# With SDK (uncomment to use SFML_HOME):
#LFLAGS = -L$(SFML_HOME)/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Standard C++ flags (Default C++17)
FLAGS = -o bin/Muffet_Game -I./include -std=c++17 # Default include path

# With SDK (uncomment to use SFML_HOME):
#FLAGS = -o bin/Muffet_Game -I$(SFML_HOME)/include -I./include -std=c++17

main: $(SRC) bin
	$(CXX) $(SRC) $(FLAGS) $(LFLAGS) 

bin:
	mkdir -p bin

clean:
	rm -r bin
