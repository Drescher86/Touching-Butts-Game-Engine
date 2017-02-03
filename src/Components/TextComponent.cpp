#include "TextComponent.h"
#include "src/TouchingButts.hpp"

void TextComponent::render()
{
	if (m_text.size() > 0) {

		if (m_transform == nullptr) {
			m_transform = gameObject->getComponent<TransformComponent>();
			if (m_transform == nullptr) {
				return;
			}
		}
		g_drawingSystem->drawText(m_text, m_transform->getPosition());
	}
}

void TextComponent::setText(std::string text)
{
	m_text = text;
}

TextComponent::TextComponent(GameObject * gameObject)
	:GuiElementComponent(gameObject)
{
}
