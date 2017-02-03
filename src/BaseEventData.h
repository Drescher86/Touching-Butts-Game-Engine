#pragma once
#include <string>
#include "GameObject.h"
/**
Base event for event system.
*/
class BaseEventData {
public:
	/**
	New base event.
	*/
	BaseEventData(std::string eventType/**Event type.*/);
	/**
	New base event.
	*/
	BaseEventData(GameObject* gameObject/**Pointer to sender.*/, std::string eventType/**Event type.*/);
	/**
	Get event type.
	*/
	std::string getEventType();
	/**
	Get game object of sender.
	*/
	GameObject* getGameObject();
	
private:
	std::string m_eventType;
	GameObject* m_gameObject;
};