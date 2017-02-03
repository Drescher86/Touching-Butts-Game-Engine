#pragma once
#include "src/Components/TextComponent.h"
#include "src/TouchingButts.hpp"
#include <string>
/**
Handles LUA script calls to the text component.
*/
class LuaTextComponentHandler {
public:
	/**
	Set text.
	*/
	static void setText(int componentId/**Text component ID.*/, std::string text/**Text to be displayed.*/);
};