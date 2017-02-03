#pragma once
#include "src/Components/TransformComponent.h"
#include "src/Vector2.h"
/**
Handles LUA script calls to the transform component.
*/
class LuaTransformComponentHandler {
public:
	/**
	Move the game object by vector.
	*/
	static void move(int componentId/**Transform component ID.*/, Vector2 moveVector/**Move vector.*/);
	/**
	Rotate the game object around z-axis.
	*/
	static void rotate(int componentId/**Transform component ID.*/, float zRotation/**Rotation in radians.*/);
	/**
	Scale the game object by vector, x width scaling and y height scaling.
	*/
	static void scale(int componentId/**Transform component ID.*/, Vector2 scale/**Scale vector.*/);
	/**
	Get game object's position.
	*/
	static Vector2 getPosition(int componentId/**Transform component ID.*/);
	/**
	Get game object's scale.
	*/
	static Vector2 getScale(int componentId/**Transform component ID.*/);
	/**
	Get rotation around z axis in radians.
	*/
	static float getRotationAroundZAxis(int componentId/**Transform component ID.*/);
	/**
	Set game object's position.
	*/
	static void setPosition(int componentId/**Transform component ID.*/, Vector2 newPosition/**New position.*/);
};