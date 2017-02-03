#include "DemoGame.h"
#include "src/TouchingButts.hpp"


int main(int argc, char** argv) {

	DemoGame * game = new DemoGame();
	int width = 1280;
	int height = 720;
    TouchingButts p(width, height, game, "Demo Game");
    p.startGameLoop();
	
    return 0;
}