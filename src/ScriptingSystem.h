#pragma once
#include "LuaBridge.h"
#include "EngineSystem.h"
#include "TouchingButts.hpp"
/**
Scripting System. Creates connection between c++ code and LUA scripts.
*/
class ScriptingSystem : public EngineSystem {
public:
	/**
	Get LUA state.
	*/
	luabridge::lua_State* getState();
	/**
	Whether LUA is updated while game runs.
	*/
	bool isLuaOnTheFlyEnabled();
	/**
	Get time between LUA updates.
	*/
	float getLuaUpdateTimer();

	
	ScriptingSystem();
	~ScriptingSystem();
protected:
	virtual bool init() override;
	virtual void postInit() override;
	virtual void shutdown() override;
private:
	luabridge::lua_State* m_lua;

	bool m_luaOnTheFlyEnabled;
	float m_luaOnTheFlyUpdateTimer;

	friend class TouchingButts;
};