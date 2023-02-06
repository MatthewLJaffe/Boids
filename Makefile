all:
	g++ -I src/include/SDL2 -L src/lib -Wall -o Boids *.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf