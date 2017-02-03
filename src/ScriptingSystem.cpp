#include "ScriptingSystem.h"
#include "GameObject.h"
#include "src/LuaHandlers/LuaSceneSystemHandler.h"
#include "src/LuaHandlers/LuaSceneHandler.h"
#include "src/LuaHandlers/LuaEventSystemHandler.h"
#include "src/LuaHandlers/LuaInputSystemHandler.h"
#include "src/LuaHandlers/LuaDebugSystemHandler.h"
#include "src/LuaHandlers/LuaGameObjectHandler.h"
#include "src/LuaHandlers/LuaTransformComponentHandler.h"
#include "src/LuaHandlers/LuaSpriteComponentHandler.h"
#include "src/LuaHandlers/LuaBox2DColliderComponentHandler.h"
#include "src/LuaHandlers/LuaCircleColliderComponentHandler.h"
#include "src/LuaHandlers/LuaRigidBodyComponentHandler.h"
#include "src/LuaHandlers/LuaScriptableComponentHandler.h"
#include "src/LuaHandlers/LuaAnimation2DComponentHandler.h"
#include "src/LuaHandlers/LuaButtonComponentHandler.h"
#include "src/LuaHandlers/LuaTextComponentHandler.h"
#include "TouchingButts.hpp"
#include "Components/RigidBodyComponent.h"
#include "SceneSystem.h"
#include "Components/CircleColliderComponent.h"
#include "Components/TextComponent.h"
#include "LuaHandlers/LuaTouchingButtsHandler.h"
luabridge::lua_State * ScriptingSystem::getState()
{
	return m_lua;
}

bool ScriptingSystem::isLuaOnTheFlyEnabled()
{
	return m_luaOnTheFlyEnabled;
}

float ScriptingSystem::getLuaUpdateTimer()
{
	return m_luaOnTheFlyUpdateTimer;
}


bool ScriptingSystem::init()
{
	EngineSystem::init();
	m_lua = luabridge::luaL_newstate();
	luaL_openlibs(m_lua);

	auto ns = getGlobalNamespace(m_lua);

	ns
		.beginClass<LuaGameObjectHandler>("gameObject")
			.addStaticFunction("getName", &LuaGameObjectHandler::getName)
			.addStaticFunction("addTransformComponent", &LuaGameObjectHandler::addComponent<TransformComponent>)
			.addStaticFunction("addScriptableComponent", &LuaGameObjectHandler::addComponent<ScriptableComponent>)
			.addStaticFunction("addSpriteComponent", &LuaGameObjectHandler::addComponent<SpriteComponent>)
			.addStaticFunction("addRigidBodyComponent", &LuaGameObjectHandler::addComponent<RigidBodyComponent>)
			.addStaticFunction("addBox2DColliderComponent", &LuaGameObjectHandler::addComponent<Box2DColliderComponent>)
			.addStaticFunction("addCircleColliderComponent", &LuaGameObjectHandler::addComponent<CircleColliderComponent>)
			.addStaticFunction("addAnimation2DComponent", &LuaGameObjectHandler::addComponent<Animation2DComponent>)
			.addStaticFunction("addButtonComponent", &LuaGameObjectHandler::addComponent<ButtonComponent>)
			.addStaticFunction("addTextComponent", &LuaGameObjectHandler::addComponent<TextComponent>)
			.addStaticFunction("getTransformComponent", &LuaGameObjectHandler::getComponentId<TransformComponent>)
			.addStaticFunction("getScriptableComponent", &LuaGameObjectHandler::getComponentId<ScriptableComponent>)
			.addStaticFunction("getSpriteComponent", &LuaGameObjectHandler::getComponentId<SpriteComponent>)
			.addStaticFunction("getRigidBodyComponent", &LuaGameObjectHandler::getComponentId<RigidBodyComponent>)
			.addStaticFunction("getBox2DColliderComponent", &LuaGameObjectHandler::getComponentId<Box2DColliderComponent>)
			.addStaticFunction("getCircleColliderComponent", &LuaGameObjectHandler::getComponentId<CircleColliderComponent>)
			.addStaticFunction("getAnimation2DComponent", &LuaGameObjectHandler::getComponentId<Animation2DComponent>)
			.addStaticFunction("getButtonComponent", &LuaGameObjectHandler::getComponentId<ButtonComponent>)
			.addStaticFunction("getTextComponent", &LuaGameObjectHandler::getComponentId<TextComponent>)
			.addStaticFunction("getParent", &LuaGameObjectHandler::getParentId)
			.addStaticFunction("removeComponent", &LuaGameObjectHandler::removeComponent)
		.endClass()
		.beginClass<Vector2>("vector2")
			.addConstructor<void(*)(float, float)>()
			.addFunction("tostring", &Vector2::toString)
			.addFunction("getX", &Vector2::x)
			.addFunction("getY", &Vector2::y)
		.endClass()
		.beginClass<LuaSceneSystemHandler>("sceneSystem")
			.addStaticFunction("loadScene", &LuaSceneSystemHandler::loadScene)
			.addStaticFunction("activateScene", &LuaSceneSystemHandler::activateScene)
			.addStaticFunction("getCurrentSceneName", &LuaSceneSystemHandler::getCurrentScene)
			.addStaticFunction("moveCamera", &LuaSceneSystemHandler::move2DCamera)
			.addStaticFunction("setCameraPosition", &LuaSceneSystemHandler::set2DCameraPosition)
		.endClass()
		.beginClass<LuaSceneHandler>("scene")
			.addStaticFunction("addGameObject", &LuaSceneHandler::addGameObject)
			.addStaticFunction("removeGameObject", &LuaSceneHandler::removeGameObject)
			.addStaticFunction("getSize", &LuaSceneHandler::getSize)
			.addStaticFunction("getGameObjectIdFromName", &LuaSceneHandler::getGameObjectIdFromName)
		.endClass()
		.beginClass<LuaEventSystemHandler>("eventSystem")
			.addStaticFunction("fireEvent", &LuaEventSystemHandler::fireEvent)
			.addStaticFunction("listenForEvent", &LuaEventSystemHandler::listenToEventType)
		.endClass()
		.beginClass<LuaInputSystemHandler>("inputSystem")
			.addStaticFunction("getKeyDown", &LuaInputSystemHandler::getKeyDown)
			.addStaticFunction("getKeyUp", &LuaInputSystemHandler::getKeyUp)
			.addStaticFunction("getKeyPressed", &LuaInputSystemHandler::getKeyPressed)
			.addStaticFunction("getKeyReleased", &LuaInputSystemHandler::getKeyReleased)
			.addStaticFunction("getWheelY", &LuaInputSystemHandler::getWheelY)
			.addStaticFunction("getMousePosition", &LuaInputSystemHandler::getMousePosition)
		.endClass()
		.beginClass<LuaDebugSystemHandler>("debugSystem")
			.addStaticFunction("writeToDebug", &LuaDebugSystemHandler::writeToDebug)
			.addStaticFunction("writeToDebugChannel", &LuaDebugSystemHandler::writeToDebugChannel)
			.addStaticFunction("createDebugFile", &LuaDebugSystemHandler::createDebugFile)
			.addStaticFunction("addChannelFilter", &LuaDebugSystemHandler::addChannelFilter)
			.addStaticFunction("removeChannelFilter", &LuaDebugSystemHandler::removeChannelFilter)
		.endClass()
		.beginClass<LuaTransformComponentHandler>("transformComponent")
			.addStaticFunction("move", &LuaTransformComponentHandler::move)
			.addStaticFunction("rotate", &LuaTransformComponentHandler::rotate)
			.addStaticFunction("scale", &LuaTransformComponentHandler::scale)
			.addStaticFunction("setPosition", &LuaTransformComponentHandler::setPosition)
			.addStaticFunction("getPosition", &LuaTransformComponentHandler::getPosition)
			.addStaticFunction("getRotationAroundZAxis", &LuaTransformComponentHandler::getRotationAroundZAxis)
			.addStaticFunction("getScale", &LuaTransformComponentHandler::getScale)
		.endClass()
		.beginClass<LuaSpriteComponentHandler>("spriteComponent")
			.addStaticFunction("getWidth", &LuaSpriteComponentHandler::width)
			.addStaticFunction("getHeight", &LuaSpriteComponentHandler::height)
			.addStaticFunction("setSprite", &LuaSpriteComponentHandler::setSpriteFromName)
			.addStaticFunction("setSortingOrder", &LuaSpriteComponentHandler::setSortingOrder)
		.endClass()
		.beginClass<LuaRigidBodyComponentHandler>("rigidBodyComponent")
			.addStaticFunction("addForce", &LuaRigidBodyComponentHandler::applyForce)
			.addStaticFunction("addImpulse", &LuaRigidBodyComponentHandler::applyImpulse)
			.addStaticFunction("setVelocity", &LuaRigidBodyComponentHandler::setVelocity)
			.addStaticFunction("getVelocity", &LuaRigidBodyComponentHandler::getVelocity)
			.addStaticFunction("setToTrigger", &LuaRigidBodyComponentHandler::setToTrigger)
		.endClass()
		.beginClass<LuaAnimation2DComponentHandler>("animation2DComponent")
			.addStaticFunction("addAnimation", &LuaAnimation2DComponentHandler::addAnimation)
			.addStaticFunction("playAnimation", &LuaAnimation2DComponentHandler::playAnimation)
			.addStaticFunction("setAnimationSpeed", &LuaAnimation2DComponentHandler::setAnimationSpeed)
			.addStaticFunction("getWidth", &LuaAnimation2DComponentHandler::width)
			.addStaticFunction("getHeight", &LuaAnimation2DComponentHandler::height)
		.endClass()
		.beginClass<LuaScriptableComponentHandler>("scriptableComponent")
			.addStaticFunction("getGameObjectId", &LuaScriptableComponentHandler::getGameObjectId)
			.addStaticFunction("callLuaFunction", &LuaScriptableComponentHandler::callLuaFunction)
			.addStaticFunction("loadScript", &LuaScriptableComponentHandler::loadScript)
		.endClass()
		.beginClass<LuaButtonComponentHandler>("buttonComponent")
			.addStaticFunction("setSprite", &LuaButtonComponentHandler::setSprite)
			.addStaticFunction("setOnClickListener", &LuaButtonComponentHandler::setOnClickListener)
		.endClass()
		.beginClass<LuaTextComponentHandler>("textComponent")
			.addStaticFunction("setText", &LuaTextComponentHandler::setText)
		.endClass()
		.beginClass<LuaTouchingButtsHandler>("touchingButts")
			.addStaticFunction("getWidth", &LuaTouchingButtsHandler::getWidth)
			.addStaticFunction("getHeight", &LuaTouchingButtsHandler::getHeight)
		.endClass()
		.beginClass<LuaBox2DColliderComponentHandler>("box2DColliderComponent")
			.addStaticFunction("setToTrigger", &LuaBox2DColliderComponentHandler::setToTrigger)
			.addStaticFunction("setIsDynamic", &LuaBox2DColliderComponentHandler::setIfDynamic)
		.endClass()
		.beginClass<LuaCircleColliderComponentHandler>("circleColliderComponent")
			.addStaticFunction("setToTrigger", &LuaCircleColliderComponentHandler::setToTrigger)
			.addStaticFunction("setIsDynamic", & LuaCircleColliderComponentHandler::setIfDynamic)
			.addStaticFunction("setRadius", &LuaCircleColliderComponentHandler::setRadius)
		.endClass()
		;
	

	initCheck();
	return true;
}

void ScriptingSystem::postInit()
{
}

void ScriptingSystem::shutdown()
{
}

ScriptingSystem::ScriptingSystem()
{
	//do nothing
}

ScriptingSystem::~ScriptingSystem()
{
	//do nothing
}
