#pragma once
#include "src/GameObject.h"
#include "src/TouchingButts.hpp"
#include "src/SceneSystem.h"
/**
Handles LUA script calls to the game object.
*/
class LuaGameObjectHandler {
public:
	/**
	Get game object name.
	*/
	static std::string getName(int id/**Game object ID.*/);
	/**
	Remove game component from game object by ID.
	*/
	static bool removeComponent(int componentId/**Component ID.*/);
	/**
	Get ID of component of type C.
	*/
	template<typename C>
	static int getComponentId(int gameObjectId/**Game object ID.*/);
	/**
	Get ID of game object parent.
	*/
	static int getParentId(int gameObjectId/**Game object ID.*/);
	/**
	Add component of type C.
	*/
	template<typename C>
	static int addComponent(int gameObjectId/**Game object ID.*/);
};


template<typename C>
int LuaGameObjectHandler::addComponent(int gameObjectId)
{
	auto go = g_sceneSystem->getCurrentScene()->getGameObjectWithId(gameObjectId);
	auto comp = go->addComponent<C>();
	return comp->getId();
}

template<typename C>
int LuaGameObjectHandler::getComponentId(int gameObjectId) {
	auto go = g_sceneSystem->getCurrentScene()->getGameObjectWithId(gameObjectId);
	auto comp = go->getComponent<C>();
	if (comp == nullptr)
		return -1;
	return comp->getId();
}