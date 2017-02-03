#include "DemoGame.h"
#include "src/TouchingButts.hpp"
#include "src/Components/RigidBodyComponent.h"
#include "src/Components/Box2DColliderComponent.h"
#include "src/Components/TextComponent.h"
#include "src/Components/ButtonComponent.h"

bool DemoGame::update(float deltaTime) {
	bool continueGame = handleInput(deltaTime);
	return continueGame;
}

void DemoGame::init()
{
	g_sceneSystem->loadScene("MenuScene", "data/GameDemoScripts/MenuScene/MenuScene.json");
	g_sceneSystem->activateScene("MenuScene");
	g_debugSystem->createDebugFile("PlayLog.txt");
}

bool DemoGame::handleInput(float deltaTime) {

	if (g_inputSystem->getKeyDown(KeyCode::QUIT) || g_inputSystem->getKeyDown(KeyCode::ESCAPE))
		return false;

	return true;
}