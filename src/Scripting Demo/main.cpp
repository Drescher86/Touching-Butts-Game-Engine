#include "ScriptingTechDemo.h"
#include "src/TouchingButts.hpp"


int main(int argc, char** argv) {

	ScriptingTechDemo * game = new ScriptingTechDemo();
	wchar_t path[1024];
	std::wcsncpy(path, L"report.txt", 1024);
	int width = 1280;
	int height = 720;
    TouchingButts p(width, height, game, "Scripting Tech Demo");
    p.startGameLoop();
	
    return 0;
}