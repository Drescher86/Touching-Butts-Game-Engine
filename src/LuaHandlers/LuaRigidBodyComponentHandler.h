#pragma once
#include "src/Components/RigidBodyComponent.h"
#include "src/TouchingButts.hpp"
#include "src/SceneSystem.h"
#include "src/Vector2.h"
/**
Handles LUA script calls to the rigid body component.
*/
class LuaRigidBodyComponentHandler {
public:
	/**
	Apply force to the physics object.
	*/
	static void applyForce(int componentId/**Rigid body component ID.*/, Vector2 forceVector/**Force vector.*/);
	/**
	Apply impulse to the physics object.
	*/
	static void applyImpulse(int componentId/**Rigid body component ID.*/, Vector2 forceVector/**Impulse vector.*/);
	/**
	Set physics object's current velocity.
	*/
	static void setVelocity(int componentId/**Rigid body component ID.*/, Vector2 vel/**Velocity vector.*/);
	/**
	Get the physics object's current velocity.
	*/
	static Vector2 getVelocity(int componentId/**Rigid body component ID.*/);
	/**
	Set whether physics object is a trigger. Defaults to false.
	*/
	static void setToTrigger(int componentId/**Rigid body component ID.*/, bool trigger/**Whether the physics object is a trigger.*/);
};