#include "PhysicsTechDemo.h"
#include "src/TouchingButts.hpp"
#include "src/Components/RigidBodyComponent.h"
#include "src/Components/Box2DColliderComponent.h"
#include "src/Components/TextComponent.h"
#include "src/Components/ButtonComponent.h"
//#include "glm/glm.hpp"

bool firstRun = true;

bool PhysicsTechDemo::update(float deltaTime) {
	
	bool continueGame = handleInput(deltaTime);
	return continueGame;
}

void PhysicsTechDemo::init()
{
	g_sceneSystem->loadScene("Scene", "data/PhysicsTechDemoScripts/scene.json");
	g_sceneSystem->activateScene("Scene");
}

bool PhysicsTechDemo::handleInput(float deltaTime) {

	if (g_inputSystem->getKeyDown(KeyCode::QUIT) || g_inputSystem->getKeyDown(KeyCode::ESCAPE))
		return false;
	if (g_inputSystem->getKeyPressed(KeyCode::D) && g_inputSystem->getKeyDown(KeyCode::LEFT_SHIFT)) {
		g_eventSystem->fireEvent(BaseEventData("toggleDebugWindow"));
	}
	return true;
}