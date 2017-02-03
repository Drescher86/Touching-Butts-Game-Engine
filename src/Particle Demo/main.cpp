#include "ParticleDemo.h"
#include "src/TouchingButts.hpp"

int main(int argc, char** argv) {

	ParticleDemo * game = new ParticleDemo();

	int width = 1280;
	int height = 720;

    TouchingButts p(width, height, game, "Particle Demo");
    p.startGameLoop();
	return 0;
}