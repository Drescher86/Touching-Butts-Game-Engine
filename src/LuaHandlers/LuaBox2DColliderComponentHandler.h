#pragma once
#include "src/TouchingButts.hpp"
#include "src/Components/Box2DColliderComponent.h"
/**
Handles calls from LUA scripts to Box2DColliderComponents.
*/
class LuaBox2DColliderComponentHandler {
public:
	static void setToTrigger(int componentId/**ID of Box2DColliderComponent.*/, bool trigger/**Whether game object is a trigger.*/);
	static void setIfDynamic(int componentId/**ID of Box2DColliderComponent.*/, bool isDynamic/**Whether physics object is dynamic.*/);
};