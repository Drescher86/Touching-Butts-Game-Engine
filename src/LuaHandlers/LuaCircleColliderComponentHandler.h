#pragma once
#include "src/TouchingButts.hpp"
#include "src/Components/CircleColliderComponent.h"
/**
Handles LUA script calls to CircleColliderComponent.
*/
class LuaCircleColliderComponentHandler {
public:
	/**
	Set whether physics object is a trigger. Defaults to false.
	*/
	static void setToTrigger(int componentId/**ID of CircleComponent.*/, bool trigger/**Whether component is a trigger.*/);
	/**
	Set whether physics object is dynamic. Defaults to false.
	*/
	static void setIfDynamic(int componentId/**ID of CircleComponent.*/, bool isDynamic/**Whether the physics object is dynamic.*/);
	/**
	Set the radius of the collider
	*/
	static void setRadius(int componentId/**ID of the CircleComponent*/, float radius/**Radius that the component should be updated to*/);

};