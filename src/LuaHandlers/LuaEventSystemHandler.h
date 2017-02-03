#pragma once
#include "src/EventSystem.h"
#include "src/TouchingButts.hpp"
#include <string>
#include "src/Components/ScriptableComponent.h"
/**
Handles LUA script calls to the EventSystem.
*/
class LuaEventSystemHandler {
public:
	/**
	Fire event to every subscriber.
	*/
	static void fireEvent(int senderObjectId/**Sender game object ID.*/, std::string message/**Message.*/);
	/**
	Subscribe to event type.
	*/
	static void listenToEventType(int listenersId/**Listener game object ID.*/, std::string eventType/**Event type.*/, std::string method/**LUA script method name.*/);
};