#pragma once
#include "src/Components/Animation2DComponent.h"

/**
Handles calls from LUA scripts to Animation2DComponents.
*/
class LuaAnimation2DComponentHandler {
public:
	/**
	Set animation speed. Defaults to
	*/
	static void setAnimationSpeed(int componentId/**ID of Animation2DComponent.*/, float animationSpeed /**Animation speed in seconds.*/);
	/**
	Play animation by name if added.
	*/
	static void playAnimation(int componentId/**ID of Animation2DComponent.*/, std::string name/**Name of animation.*/);
	/**
	Add animation by name if exists.
	*/
	static void addAnimation(int componentId/**ID of Animation2DComponent.*/, std::string name/**Name of animation.*/);
	/**
	Get animation sprite width.
	*/
	static int width(int componentid/**ID of Animation2DComponent.*/);
	/**
	Get animation sprite height.
	*/
	static int height(int componentid/**ID of Animation2DComponent.*/);
};