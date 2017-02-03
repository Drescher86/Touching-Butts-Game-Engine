#include "src/LuaHandlers/LuaScriptableComponentHandler.h"
#include "src/TouchingButts.hpp"
#include "src/SceneSystem.h"


void LuaScriptableComponentHandler::loadScript(int componentId, std::string filename, std::string tableName)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto script = std::dynamic_pointer_cast<ScriptableComponent>(comp);
		if (script != nullptr) {
			script->loadScript(filename, tableName);
			script->onAwake();
		}
	}
}

int LuaScriptableComponentHandler::getGameObjectId(int componentId)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto script = std::dynamic_pointer_cast<ScriptableComponent>(comp);
		if (script != nullptr) {
			return script->getGameObjectId();
		}
	}
	return -1;
}

luabridge::LuaRef LuaScriptableComponentHandler::callLuaFunction(int componentId, std::string method, luabridge::LuaRef arguments)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto script = std::dynamic_pointer_cast<ScriptableComponent>(comp);
		if (script != nullptr) {
			luabridge::LuaRef r = script->callLuaFunction(method, arguments);
			return r;
		}
	}
}
