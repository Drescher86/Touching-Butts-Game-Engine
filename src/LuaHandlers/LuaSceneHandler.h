#pragma once
#include "src/Scene.h"
#include "src/TouchingButts.hpp"
#include "src/SceneSystem.h"
#include <string>
/**
Handles LUA script calls to a scene.
*/
class LuaSceneHandler {
public:
	/**
	Add a new game object to a scene.
	*/
	static int addGameObject(std::string sceneName/**Name of scene.*/, std::string name/**Name of game object. Must be unique.*/);
	/**
	Remove game object.
	*/
	static bool removeGameObject(std::string sceneName/**Scene name*/, int gameObjectId/**Game object ID.*/);
	/**
	Get number of game objects in a scene.
	*/
	static int getSize(std::string sceneName/**Name of scene.*/);
	/**
	Get game object ID from name.
	*/
	static int getGameObjectIdFromName(std::string sceneName/**Name of scene.*/, std::string name/**Name of game object.*/);
};