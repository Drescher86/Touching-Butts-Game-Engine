#include "LuaSceneHandler.h"

int LuaSceneHandler::addGameObject(std::string sceneName, std::string name)
{
	auto scene = g_sceneSystem->getSceneWithName(sceneName);
	if (scene == nullptr)
		return -1;

	auto go = scene->addGameObject(name);
	return go->getId();
}

bool LuaSceneHandler::removeGameObject(std::string sceneName, int gameObjectId)
{
	auto scene = g_sceneSystem->getSceneWithName(sceneName);
	if (scene == nullptr)
		return false;
	auto go = scene->getGameObjectWithId(gameObjectId);
	if (go != nullptr)
	{
		scene->removeGameObject(go);
		return true;
	}
	return false;
}

int LuaSceneHandler::getSize(std::string sceneName)
{
	auto scene = g_sceneSystem->getSceneWithName(sceneName);
	if(scene != nullptr)
		return scene->getSize();
	return -1;
}

int LuaSceneHandler::getGameObjectIdFromName(std::string sceneName, std::string name)
{
	auto scene = g_sceneSystem->getSceneWithName(sceneName);
	if (scene == nullptr)
		return -1;
	return scene->getGameObjectIdFromName(name);
}

