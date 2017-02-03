#pragma once

#include "src/TouchingButts.hpp"
#include "src/SceneSystem.h"
#include "LuaBridge.h"
#include <string>
/**
Handle LUA script calls to the scene system.
*/
class LuaSceneSystemHandler {
public:
	/**
	Load scene from json file.
	*/
	static void loadScene(std::string sceneName/**Name of scene.*/, std::string jsonFile/**string and name of json file.*/);
	/**
	Activate scene by name.
	*/
	static void activateScene(std::string sceneName/**Scene name.*/);
	/**
	Get current active scene.
	*/
	static std::string getCurrentScene();
	/**
	Move 2D camera.
	*/
	static void move2DCamera(Vector2 moveVector/**Move vector.*/);
	/**
	Set 2D camera position.
	*/
	static void set2DCameraPosition(Vector2 position/**Position vector.*/);
	static void init(std::shared_ptr<luabridge::Namespace> state);
};