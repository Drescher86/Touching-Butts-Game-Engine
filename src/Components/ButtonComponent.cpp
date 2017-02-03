#include "ButtonComponent.h"
#include "TextComponent.h"
#include "src/TouchingButts.hpp"

void ButtonComponent::update(float deltaTime)
{
	if (withinBoundaries())
	{
		if(g_inputSystem->getKeyPressed(KeyCode::LEFT_MOUSE_BUTTON)) {
			if (onClick != nullptr) {
				onClick();
			}
		}
	}
}

ButtonComponent::ButtonComponent(GameObject * gameObject)
	:GuiElementComponent(gameObject)
{
	onClick = []() {
		g_debugSystem->writeToDebug("Clicked");
	};
	auto text = gameObject->addComponent<TextComponent>();
	text->setText("I like monkeys");
}

bool ButtonComponent::withinBoundaries()
{
	glm::vec3 move = glm::vec3();
	if (m_followCamera) {
		move = g_sceneSystem->getCameraPosition();
	}
	if (m_transform == nullptr) {
		m_transform = gameObject->getComponent<TransformComponent>();
		if (m_transform == nullptr) {
			return false;
		}
	}
	glm::vec3 worldSpaceLoc = move + m_transform->getPosition();
	glm::vec2 mousePosition = g_inputSystem->getMousePosition();
	if (mousePosition.x >= worldSpaceLoc.x && mousePosition.x <= worldSpaceLoc.x + m_sprite->width() * m_transform->getScale().x &&
		mousePosition.y >= worldSpaceLoc.y && mousePosition.y <= worldSpaceLoc.y + m_sprite->height() * m_transform->getScale().y) {
		return true;
	}
	return false;
}
