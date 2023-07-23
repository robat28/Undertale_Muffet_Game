main: src/main.cpp bin
	clang++ src/main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o bin/main

bin: 
	mkdir -p bin
