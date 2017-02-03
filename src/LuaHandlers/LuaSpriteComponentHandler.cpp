#include "src/LuaHandlers/LuaSpriteComponentHandler.h"
#include "src/TouchingButts.hpp"
#include "src/SceneSystem.h"

int LuaSpriteComponentHandler::width(int componentid)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentid);
	if (comp != nullptr) {
		auto sprite = std::dynamic_pointer_cast<SpriteComponent>(comp);
		if (sprite != nullptr)
			return sprite->width();
	}
	return -1;
}

int LuaSpriteComponentHandler::height(int componentid)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentid);
	if (comp != nullptr) {
		auto sprite = std::dynamic_pointer_cast<SpriteComponent>(comp);
		if (sprite != nullptr)
			return sprite->height();
	}
	return -1;
}

void LuaSpriteComponentHandler::setSpriteFromName(int componentid, std::string name)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentid);
	if (comp != nullptr) {
		auto sprite = std::dynamic_pointer_cast<SpriteComponent>(comp);
		if (sprite != nullptr)
			sprite->setSpriteFromName(name);
	}
}

void LuaSpriteComponentHandler::setSortingOrder(int componentid, int order)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentid);
	if (comp != nullptr) {
		auto sprite = std::dynamic_pointer_cast<SpriteComponent>(comp);
		if (sprite != nullptr)
			sprite->setSortingOrder(order);
	}
}
