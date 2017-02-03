#include "ScriptingTechDemo.h"
#include "src/TouchingButts.hpp"
#include "src/Components/RigidBodyComponent.h"
#include "src/Components/Box2DColliderComponent.h"
#include "src/Components/TextComponent.h"
#include "src/Components/ButtonComponent.h"
//#include "glm/glm.hpp"

bool firstRun = true;

bool ScriptingTechDemo::update(float deltaTime) {
	bool continueGame = handleInput(deltaTime);
	return continueGame;
}

void ScriptingTechDemo::init()
{
	g_sceneSystem->loadScene("scene", "data/ScriptingTechDemoScripts/scene.json");
	g_sceneSystem->activateScene("scene");
}

bool ScriptingTechDemo::handleInput(float deltaTime) {

	if (g_inputSystem->getKeyDown(KeyCode::QUIT) || g_inputSystem->getKeyDown(KeyCode::ESCAPE))
		return false;

	return true;
}