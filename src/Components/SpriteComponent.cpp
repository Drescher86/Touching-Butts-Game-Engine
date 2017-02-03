#include "SpriteComponent.h"
#include "src/TouchingButts.hpp"
#include "src/SpriteSystem.h"
#include "src/DrawingSystem.h"
#include "TransformComponent.h"

int SpriteComponent::width() {
	if (m_sprite != nullptr) {
		return m_sprite->width();
	}
	return 0;
}

int SpriteComponent::height() {
	if (m_sprite != nullptr) {
		return m_sprite->height();
	}
	return 0;
}

std::shared_ptr<SRE::Mesh> SpriteComponent::getMesh() {
	return m_sprite->getMesh();
}

void SpriteComponent::setSpriteFromName(std::string name)
{
	m_sprite = g_spriteSystem->getSprite(name);
}

void SpriteComponent::setSprite(std::shared_ptr<Sprite> sprite)
{
	m_sprite = sprite;
}

SpriteComponent::SpriteComponent(GameObject * gameObject)
	: GameComponent(gameObject)
{
}

void SpriteComponent::setSortingOrder(int order)
{
	m_sortingOrder = order;
}

void SpriteComponent::render()
{
	auto transform = gameObject->getComponent<TransformComponent>();
	assert(transform.get() != nullptr && "transform of gameobject with spritecomponent is nullptr");
	if (transform.get() != nullptr) {
		g_drawingSystem->draw(m_sprite, transform->getGlobalTransform(), 0, m_sortingOrder);
	}
}
