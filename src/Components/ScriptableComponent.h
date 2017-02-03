#pragma once
#include "GameComponent.h"
#include "ColliderComponent.h"
#include "GameComponent.h"
#include <string>
#include <vector>
#include <map>

#include <LuaBridge.h>
#include "lua.h"
#include "src/IEventListener.h"
#include "src/TouchingButts.hpp"
#include "RigidBodyComponent.h"
#include "src/SceneSystem.h"

class ScriptableComponent : public GameComponent, public IEventListener {
public:
	
	void loadScript(std::string filename, std::string tableName);

	void onAwake();
	void onStart();
	
	void prePhysicsUpdate() override;
	void postPhysicsUpdate() override;
	void preRenderUpdate() override;
	void postRenderUpdate() override;
	void onDestroy();
	void onCollisionEnter(std::shared_ptr<ColliderComponent> other);
	void onCollisionStay(std::shared_ptr<ColliderComponent> other);
	void onCollisionExit(std::shared_ptr<ColliderComponent> other);

	luabridge::LuaRef callLuaFunction(std::string method, luabridge::LuaRef arguments);

	//Methods exposed for script
	void listenForEvent(std::string eventType, std::string method);
	void cloneGameObject();
	int getGameObjectId();
	

	
protected:
	void update(float deltaTime) override;
	ScriptableComponent(GameObject * gameObject);
private:
	luabridge::lua_State* m_lua;
	std::string m_tableName;
	std::string m_filename;
	std::shared_ptr<luabridge::LuaRef> m_self;

	float m_updateTimer;
	
	std::shared_ptr<luabridge::LuaRef> m_table;

	bool m_firstUpdate = true;

	std::map<std::string, std::vector<std::string>> m_eventMap;

	friend class GameObject;

	// Inherited via IEventListener
	virtual void onEvent(BaseEventData eventData) override;
	void checkFileUpdate(float deltaTime);
};

