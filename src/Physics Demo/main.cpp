#include "PhysicsTechDemo.h"
#include "src/TouchingButts.hpp"


int main(int argc, char** argv) {

	PhysicsTechDemo * game = new PhysicsTechDemo();
	wchar_t path[1024];
	std::wcsncpy(path, L"report.txt", 1024);
	int width = 1280;
	int height = 720;
    TouchingButts p(width, height, game, "Physics Tech Demo");
    p.startGameLoop();
	
    return 0;
}