#include "LuaGameObjectHandler.h"

std::string LuaGameObjectHandler::getName(int id)
{
	auto go = g_sceneSystem->getCurrentScene()->getGameObjectWithId(id);
	if(go != nullptr)
		return go->getName();
	return "";
}

bool LuaGameObjectHandler::removeComponent(int componentId)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		comp->getGameObject()->removeComponent(comp);

		return true;
	}
	return false;
}


int LuaGameObjectHandler::getParentId(int gameObjectId)
{
	auto go = g_sceneSystem->getCurrentScene()->getGameObjectWithId(gameObjectId);
	if (go != nullptr) {
		auto parent = go->getParent();
		if (parent != nullptr)
			return parent->getId();
	}
	return -1;
}
