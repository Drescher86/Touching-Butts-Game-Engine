#include "src/LuaHandlers/LuaAnimation2DComponentHandler.h"
#include "src/TouchingButts.hpp"
#include "src/SceneSystem.h"

void LuaAnimation2DComponentHandler::setAnimationSpeed(int componentId, float animationSpeed)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto anim = std::dynamic_pointer_cast<Animation2DComponent>(comp);
		if (anim != nullptr) {
			anim->setAnimationSpeed(animationSpeed);
		}
	}
}

void LuaAnimation2DComponentHandler::playAnimation(int componentId, std::string name)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto anim = std::dynamic_pointer_cast<Animation2DComponent>(comp);
		if (anim != nullptr) {
			anim->playAnimation(name);
		}
	}
}

void LuaAnimation2DComponentHandler::addAnimation(int componentId, std::string name)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto anim = std::dynamic_pointer_cast<Animation2DComponent>(comp);
		if (anim != nullptr) {
			anim->addAnimation(name);
		}
	}
}

int LuaAnimation2DComponentHandler::width(int componentid)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentid);
	if (comp != nullptr) {
		auto anim = std::dynamic_pointer_cast<Animation2DComponent>(comp);
		if (anim != nullptr) {
			return anim->width();
		}
	}
	return -1;
}

int LuaAnimation2DComponentHandler::height(int componentid)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentid);
	if (comp != nullptr) {
		auto anim = std::dynamic_pointer_cast<Animation2DComponent>(comp);
		if (anim != nullptr) {
			return anim->height();
		}
	}
	return -1;
}
