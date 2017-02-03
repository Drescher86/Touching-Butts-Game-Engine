#include "ScriptableComponent.h"
#include "CircleColliderComponent.h"
#include "src/ScriptingSystem.h"
#include "src/TouchingButts.hpp"
#include <iostream>
#include <time.h>

using namespace luabridge;

ScriptableComponent::ScriptableComponent(GameObject * gameObject)
	: GameComponent(gameObject), m_updateTimer(0) {
	m_lua = g_scriptingSystem->getState();
}

void ScriptableComponent::onAwake()
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef onAwakeFunc = table["onAwake"];
		if (onAwakeFunc.isFunction()) {
			LuaRef ref = onAwakeFunc(getId());
			if (ref.isTable()) {
				auto dontDestroy = ref["dontDestroyOnLoad"];
				if (dontDestroy.isString() && dontDestroy.cast<std::string>() == "true") {
					gameObject->setIndestructible(true);
				}
			}
			m_self = std::make_shared<LuaRef>(ref);
		}
	}
}

void ScriptableComponent::onStart()
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef onStartFunc = table["onStart"];
		if (onStartFunc.isFunction()) {
			onStartFunc(*m_self.get());
		}
	}
}

void ScriptableComponent::update(float deltaTime)
{
	checkFileUpdate(deltaTime);
	if (m_firstUpdate)
	{
		onStart();
		m_firstUpdate = false;
	}
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef updateFunc = table["update"];
		if (updateFunc.isFunction()) {
			updateFunc(*m_self.get(), deltaTime);
		}
	}
}

void ScriptableComponent::prePhysicsUpdate()
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef prePhysicsUpdateFunc = table["prePhysicsUpdate"];
		if (prePhysicsUpdateFunc.isFunction()) {
			prePhysicsUpdateFunc(*m_self.get());
		}
	}
}

void ScriptableComponent::postPhysicsUpdate()
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef postPhysicsUpdateFunc = table["postPhysicsUpdate"];
		if (postPhysicsUpdateFunc.isFunction()) {
			postPhysicsUpdateFunc(*m_self.get());
		}
	}
}

void ScriptableComponent::preRenderUpdate()
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef preRenderingUpdateFunc = table["preRenderUpdate"];
		if (preRenderingUpdateFunc.isFunction()) {
			preRenderingUpdateFunc(*m_self.get());
		}
	}

}

void ScriptableComponent::postRenderUpdate()
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef postRenderingUpdateFunc = table["postRenderUpdate"];
		if (postRenderingUpdateFunc.isFunction()) {
			postRenderingUpdateFunc(*m_self.get());
		}
	}
	
}

void ScriptableComponent::onDestroy()
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef onDestroyFunc = table["onDestroy"];
		if (onDestroyFunc.isFunction()) {
			onDestroyFunc(*m_self.get());
		}
	}
	
}

void ScriptableComponent::onCollisionEnter(std::shared_ptr<ColliderComponent> other)
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef onCollisionEnterFunc = table["onCollisionEnter"];
		if (onCollisionEnterFunc.isFunction()) {
			onCollisionEnterFunc(*m_self.get(), other->getGameObject()->getId());
		}
	}
	
}

void ScriptableComponent::onCollisionStay(std::shared_ptr<ColliderComponent> other)
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef onCollisionStayFunc = table["onCollisionStay"];
		if (onCollisionStayFunc.isFunction()) {
			onCollisionStayFunc(*m_self.get(), other->getGameObject()->getId());
		}
	}
}

void ScriptableComponent::onCollisionExit(std::shared_ptr<ColliderComponent> other)
{
	if (other == nullptr)
		return;
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef onCollisionExitFunc = table["onCollisionExit"];
		if (onCollisionExitFunc.isFunction()) {
			onCollisionExitFunc(*m_self.get(), other->getGameObject()->getId());
		}
	}
	
}

LuaRef ScriptableComponent::callLuaFunction(std::string method, LuaRef arguments)
{
	LuaRef table = getGlobal(m_lua, m_tableName.c_str());
	if (table.isTable()) {
		LuaRef func = table[method];
		if (func.isFunction()) {
			if (arguments.isNil())
				return func(*m_self.get());
			else
				return func(*m_self.get(), arguments);
		}
	}
}


void ScriptableComponent::listenForEvent(std::string eventType, std::string method) {
	std::transform(eventType.begin(), eventType.end(), eventType.begin(), ::tolower);
	auto item = m_eventMap.find(eventType);
	if (item == m_eventMap.end()) {
		std::vector<std::string> methods;
		methods.push_back(method);
		m_eventMap.insert(std::pair<std::string, std::vector<std::string>>(eventType, methods));
	}
	else {
		item->second.push_back(method);
	}
}

void ScriptableComponent::cloneGameObject()
{
	gameObject->clone();
}

int ScriptableComponent::getGameObjectId() {
	return GameComponent::getGameObject()->getId();
}


void ScriptableComponent::onEvent(BaseEventData eventData) {
	auto item = m_eventMap.find(eventData.getEventType());
	if (item != m_eventMap.end()) {

		std::vector<std::string>::iterator it = item->second.begin();
		for (; it != item->second.end(); it++) {
			if (luaL_dofile(m_lua, m_filename.c_str()) == 0) {
				LuaRef table = getGlobal(m_lua, m_tableName.c_str());
				if (table.isTable()) {
					LuaRef function = table[*it];
					if (function.isFunction()) {
						function(*m_self.get());
					}
				}
			}
		}
	}
}

void ScriptableComponent::checkFileUpdate(float deltaTime)
{
	if (g_scriptingSystem->isLuaOnTheFlyEnabled()) {
		m_updateTimer += deltaTime;
		if (g_scriptingSystem->getLuaUpdateTimer() <= m_updateTimer) {
			luaL_dofile(m_lua, m_filename.c_str());
			m_updateTimer = 0;
		}
	}
}

void ScriptableComponent::loadScript(std::string filename, std::string tableName)
{
	m_filename = filename;
	m_tableName = tableName;
	auto result = luaL_dofile(m_lua, filename.c_str());
	if(result != 0) {
		std::cout << "script " << filename << " couldn't open";
		fprintf(stderr, "luaL_dofile failed: %s\n", lua_tostring(m_lua, -1));
	}
	else {
		m_table = std::make_shared<LuaRef>(getGlobal(m_lua, m_tableName.c_str()));
		assert(m_table->isTable() && "LUA Table is not a table");
	}
}
