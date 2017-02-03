#include "LuaTextComponentHandler.h"

void LuaTextComponentHandler::setText(int componentId, std::string text)
{
	auto comp = g_sceneSystem->getCurrentScene()->getComponentWithId(componentId);
	if (comp != nullptr) {
		auto textComp = std::dynamic_pointer_cast<TextComponent>(comp);
		if (textComp != nullptr)
			return textComp->setText(text);
	}
}
