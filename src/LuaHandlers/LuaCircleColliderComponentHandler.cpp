#include "LuaCircleColliderComponentHandler.h"

void LuaCircleColliderComponentHandler::setToTrigger(int componentId, bool trigger)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto collider = std::dynamic_pointer_cast<CircleColliderComponent>(comp);
		if (collider != nullptr)
			return collider->setToTrigger(trigger);
	}
}

void LuaCircleColliderComponentHandler::setIfDynamic(int componentId, bool isDynamic)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto collider = std::dynamic_pointer_cast<CircleColliderComponent>(comp);
		if (collider != nullptr)
			return collider->setIfDynamic(isDynamic);
	}
}

void LuaCircleColliderComponentHandler::setRadius(int componentId, float radius)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto collider = std::dynamic_pointer_cast<CircleColliderComponent>(comp);
		if (collider != nullptr)
			return collider->setRadius(radius);
	}
}
