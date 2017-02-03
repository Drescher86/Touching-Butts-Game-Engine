#include "LuaRigidBodyComponentHandler.h"

void LuaRigidBodyComponentHandler::applyForce(int componentId, Vector2 forceVector)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto rigidBody = std::dynamic_pointer_cast<RigidBodyComponent>(comp);
		if (rigidBody != nullptr)
			rigidBody->applyForce(forceVector);
	}
}

void LuaRigidBodyComponentHandler::applyImpulse(int componentId, Vector2 forceVector)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto rigidBody = std::dynamic_pointer_cast<RigidBodyComponent>(comp);
		if (rigidBody != nullptr)
			rigidBody->applyImpulse(forceVector);
	}
}

void LuaRigidBodyComponentHandler::setVelocity(int componentId, Vector2 vel)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto rigidBody = std::dynamic_pointer_cast<RigidBodyComponent>(comp);
		if (rigidBody != nullptr)
			rigidBody->setVelocity(vel);
	}
}

Vector2 LuaRigidBodyComponentHandler::getVelocity(int componentId)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto rigidBody = std::dynamic_pointer_cast<RigidBodyComponent>(comp);
		if (rigidBody != nullptr)
			return rigidBody->getVelocity();
	}
}

void LuaRigidBodyComponentHandler::setToTrigger(int componentId, bool trigger)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr)
	{
		auto rigidBody = std::dynamic_pointer_cast<RigidBodyComponent>(comp);
		if (rigidBody != nullptr)
			return rigidBody->setToTrigger(trigger);
	}
}



