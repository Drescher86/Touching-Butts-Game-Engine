#pragma once
#include "src/InputSystem.h"
#include "src/TouchingButts.hpp"
#include "src/Vector2.h"
#include <string>
#include <map>

static bool isInitialized = false;
enum KeyCode;
/**
Handles LUA script calls to the input system.
*/
class LuaInputSystemHandler {
public:
	/**
	Get if key down by string. Must match the enum name of the key code.
	*/
	static bool getKeyDown(std::string keyCode/**Name of key code.*/);
	/**
	Get if key up by string. Must match the enum name of the key code.
	*/
	static bool getKeyUp(std::string  keyCode/**Name of key code.*/);
	/**
	Get if key pressed, true only once per click. Must match the enum name of the key code.
	*/
	static bool getKeyPressed(std::string  keyCode/**Name of key code.*/);
	/**
	Get if key released, true only once per click. Must match the enum name of the key code.
	*/
	static bool getKeyReleased(std::string  keyCode/**Name of key code.*/);
	/**
	Get scroll wheel.
	*/
	static float getWheelY();
	/**
	Get the 2D world coordinates of the mouse.
	*/
	static Vector2 getMousePosition();
private:
	static std::string toLower(std::string str);
	static void init();
	static std::map<std::string, KeyCode> m_stringToKeyMap;
};

