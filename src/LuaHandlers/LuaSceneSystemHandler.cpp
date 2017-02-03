#include "LuaSceneSystemHandler.h"

void LuaSceneSystemHandler::loadScene(std::string sceneName, std::string jsonFile)
{
	g_sceneSystem->loadScene(sceneName, jsonFile);
}

void LuaSceneSystemHandler::activateScene(std::string sceneName)
{
	g_sceneSystem->activateScene(sceneName);
	
}

std::string LuaSceneSystemHandler::getCurrentScene()
{
	return g_sceneSystem->getCurrentScene()->getName();
}

void LuaSceneSystemHandler::move2DCamera(Vector2 moveVector)
{
	g_sceneSystem->move2DCamera(moveVector);
}

void LuaSceneSystemHandler::set2DCameraPosition(Vector2 position)
{
	g_sceneSystem->set2DCameraPosition(position);
}

void LuaSceneSystemHandler::init(std::shared_ptr<luabridge::Namespace> ns)
{
		
}
