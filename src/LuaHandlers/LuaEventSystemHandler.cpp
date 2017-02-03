#include "LuaEventSystemHandler.h"

void LuaEventSystemHandler::fireEvent(int senderObjectId, std::string message)
{
	auto sender = g_sceneSystem->getCurrentScene()->getGameObjectWithId(senderObjectId);
	if (sender != nullptr)
	{
		BaseEventData eventData(sender.get(), message);
		g_eventSystem->fireEvent(eventData);
	}
}

void LuaEventSystemHandler::listenToEventType(int listenersId, std::string eventType, std::string method)
{
	auto c = g_sceneSystem->getCurrentScene()->getComponentWithId(listenersId);
	auto comp = std::dynamic_pointer_cast<ScriptableComponent>(c);
	if (comp != nullptr) {
		std::shared_ptr<IEventListener> sharedPtr(comp);
		g_eventSystem->listenToEventType(sharedPtr, eventType);
		comp->listenForEvent(eventType, method);
	}
}
