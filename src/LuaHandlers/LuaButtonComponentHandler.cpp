#include "LuaButtonComponentHandler.h"
#include "LuaEventSystemHandler.h"

void LuaButtonComponentHandler::setSprite(int componentId, std::string name)
{
	auto component = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (component != nullptr) {
		auto button = std::dynamic_pointer_cast<ButtonComponent>(component);
		if (button != nullptr) {
			button->setSprite(name);
		}
	}
}

void LuaButtonComponentHandler::setOnClickListener(int buttonId, int scriptId, std::string methodName)
{
	auto component = g_sceneSystem->getCurrentScene()->getComponentWithId(buttonId);
	if (component != nullptr) {
		auto button = std::dynamic_pointer_cast<ButtonComponent>(component);
		if (button != nullptr) {
			std::string eventType = std::to_string(buttonId) + "-" + std::to_string(scriptId) + "-method:" + methodName;
			LuaEventSystemHandler::listenToEventType(scriptId, eventType, methodName);
			button->onClick = [eventType]() { g_eventSystem->fireEvent(BaseEventData(eventType)); };
		}
	}
}


