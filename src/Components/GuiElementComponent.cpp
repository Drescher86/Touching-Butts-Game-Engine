#include "GuiElementComponent.h"
#include "src/TouchingButts.hpp"

void GuiElementComponent::setFollowCamera(bool followCamera)
{
	m_followCamera = followCamera;
}

void GuiElementComponent::setSprite(std::string name)
{
	m_sprite = g_spriteSystem->getSprite(name);
}

void GuiElementComponent::render()
{
	if (m_transform == nullptr) {
		m_transform = gameObject->getComponent<TransformComponent>();
		if (m_transform == nullptr) {
			return;
		}
	}
	auto trans = glm::mat4(0);
	trans[3][3] = -1;
	if (m_sprite != nullptr) {
		if (m_followCamera) {
			auto gt = m_transform->getGlobalTransform();
			auto ct = g_sceneSystem->getViewTransform() * trans;
			auto tra = gt + ct;
			tra[3][3] = 1;
			g_drawingSystem->drawUI(m_sprite, tra);
		}
		else {
			g_drawingSystem->drawUI(m_sprite, m_transform->getGlobalTransform());
		}
	}
}

GuiElementComponent::GuiElementComponent(GameObject * gameObject)
	:GameComponent(gameObject)
{

}
