#pragma once
#include "src/Components/SpriteComponent.h"
/**
Handles LUA script calls to sprite component.
*/
class LuaSpriteComponentHandler {
public:
	/**
	Get sprite width.
	*/
	static int width(int componentid/**Sprite component ID.*/);
	/**
	Get sprite height.
	*/
	static int height(int componentid/**Sprite component ID.*/);
	/**
	Set sprite from name.
	*/
	static void setSpriteFromName(int componentid/**Sprite component ID.*/, std::string name/**Name of sprite.*/);
	/**
	Set sorting order. Defaults to 1. Negative away from camera, positive toward camera.
	*/
	static void setSortingOrder(int componentid/**Sprite component ID.*/, int order/**Sorting order.*/);
};