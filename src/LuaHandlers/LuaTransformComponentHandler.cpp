#include "LuaTransformComponentHandler.h"
#include "src/TouchingButts.hpp"
#include "src/SceneSystem.h"
#include "glm/glm.hpp"

void LuaTransformComponentHandler::move(int componentId, Vector2 moveVector)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto trans = std::dynamic_pointer_cast<TransformComponent>(comp);
		if (trans != nullptr) {
			trans->move2D(moveVector);
		}
	}
}

void LuaTransformComponentHandler::rotate(int componentId, float zRotation)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto trans = std::dynamic_pointer_cast<TransformComponent>(comp);
		if (trans != nullptr) {
			trans->rotate(glm::vec3(0,0,zRotation));
		}
	}
}

void LuaTransformComponentHandler::scale(int componentId, Vector2 scale)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto trans = std::dynamic_pointer_cast<TransformComponent>(comp);
		if (trans != nullptr) {
			trans->scale(glm::vec3(scale.x(), scale.y(), 1));
		}
	}
}

Vector2 LuaTransformComponentHandler::getPosition(int componentId)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	assert(comp != nullptr && "no component with that id - LuaTransformComponentHandler");
	if (comp != nullptr) {
		auto trans = std::dynamic_pointer_cast<TransformComponent>(comp);
		assert(trans != nullptr && "The compoenent with that id is not a transform - LuaTransformComponentHandler");
		if (trans != nullptr) {
			return Vector2(trans->getPosition().x, trans->getPosition().y);
		}
	}
}

Vector2 LuaTransformComponentHandler::getScale(int componentId)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	assert(comp != nullptr && "no component with that id - LuaTransformComponentHandler");
	if (comp != nullptr) {
		auto trans = std::dynamic_pointer_cast<TransformComponent>(comp);
		assert(trans != nullptr && "The compoenent with that id is not a transform - LuaTransformComponentHandler");
		if (trans != nullptr) {
			return Vector2(trans->getScale().x, trans->getScale().y);
		}
	}
}

float LuaTransformComponentHandler::getRotationAroundZAxis(int componentId)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	assert(comp != nullptr && "no component with that id - LuaTransformComponentHandler");
	if (comp != nullptr) {
		auto trans = std::dynamic_pointer_cast<TransformComponent>(comp);
		assert(trans != nullptr && "The compoenent with that id is not a transform - LuaTransformComponentHandler");
		if (trans != nullptr) {
			return trans->getRotationAroundZAxis();
		}
	}
}

void LuaTransformComponentHandler::setPosition(int componentId, Vector2 newPosition)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	assert(comp != nullptr && "no component with that id - LuaTransformComponentHandler");
	if (comp != nullptr) {
		auto trans = std::dynamic_pointer_cast<TransformComponent>(comp);
		assert(trans != nullptr && "The compoenent with that id is not a transform - LuaTransformComponentHandler");
		if (trans != nullptr) {
			return trans->setPosition(glm::vec3(newPosition.x(), newPosition.y(), 0));
		}
	}
}
