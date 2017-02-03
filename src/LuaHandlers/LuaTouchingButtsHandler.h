#pragma once
#include "src/TouchingButts.hpp"
/**
Handles LUA script calls to touching butts main class.
*/
class LuaTouchingButtsHandler {
public:
	/**
	Get height of game window.
	*/
	static int getHeight();
	/**
	Get width of game window.
	*/
	static int getWidth();

};