#pragma once
#include "src/Components/ButtonComponent.h"
#include "src/TouchingButts.hpp"
#include <string>
#include "src/SceneSystem.h"
/**
Handles calls from LUA scripts to ButtonComponent.
*/
class LuaButtonComponentHandler {
public:
	/**
	Set sprite by name.
	*/
	static void setSprite(int componentId/**ID of ButtonCollider.*/, std::string name/**Name of sprite.*/);
	/**
	Set on click listener on button.
	*/
	static void setOnClickListener(int buttonId/**ID of ButtonCollider.*/, int scriptId/**Script ID.*/, std::string methodName/**Method name in LUA script.*/);
};