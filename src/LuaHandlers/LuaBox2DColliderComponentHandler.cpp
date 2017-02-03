#include "LuaBox2DColliderComponentHandler.h"

void LuaBox2DColliderComponentHandler::setToTrigger(int componentId, bool trigger)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto collider = std::dynamic_pointer_cast<Box2DColliderComponent>(comp);
		if (collider != nullptr)
			return collider->setToTrigger(trigger);
	}
}

void LuaBox2DColliderComponentHandler::setIfDynamic(int componentId, bool isDynamic)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto collider = std::dynamic_pointer_cast<Box2DColliderComponent>(comp);
		if (collider != nullptr)
			return collider->setIfDynamic(isDynamic);
	}
}
