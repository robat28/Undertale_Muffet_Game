
main: src/main.cpp src/Game.cpp src/Player.cpp src/Enemy.cpp src/Playfield.cpp src/GUI.cpp bin
	clang++ src/main.cpp src/Game.cpp src/Player.cpp src/Enemy.cpp src/Playfield.cpp src/GUI.cpp -lsfml-graphics -lsfml-window -lsfml-system -o bin/main -I./include/

bin: 
	mkdir -p bin
