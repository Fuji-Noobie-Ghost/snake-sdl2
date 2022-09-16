build:
	clear
	g++ main.cpp */*.cpp --std=c++14 -o ./bin/snake -I headers -I include -L lib -l SDL2main -l SDL2

run:
	clear
	./bin/snake