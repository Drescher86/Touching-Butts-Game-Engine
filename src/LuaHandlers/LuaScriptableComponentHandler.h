#pragma once
#include "src/Components/ScriptableComponent.h"
/**
Handles LUA script calls to scriptable component.
*/
class LuaScriptableComponentHandler {
public:
	/**
	Load script into component from json file.
	*/
	static void loadScript(int componentId/**Scritable component ID.*/, std::string filename/**File path and name.*/, std::string tableName/**Lua table name.*/);
	/**
	Get game object ID.
	*/
	static int getGameObjectId(int componentId/**Scriptable component ID.*/);
	/**
	*/
	static luabridge::LuaRef callLuaFunction(int componentId, std::string method, luabridge::LuaRef arguments);
};
template<typename C>
inline int LuaScriptableComponentHandler::addComponent(int gameObjectID)
{
	return 0;
}
