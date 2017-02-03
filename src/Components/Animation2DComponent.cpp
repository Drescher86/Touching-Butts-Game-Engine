#include "Animation2DComponent.h"
#include "src/TouchingButts.hpp"

void Animation2DComponent::setAnimationSpeed(float animationSpeed)
{
	m_animationSpeed = animationSpeed;
}

void Animation2DComponent::playAnimation(std::string name)
{
	m_activeAnimation = name;
	m_frameCount = m_spriteMap[name]->frameCount();
	m_frameCounter = 0;
}

void Animation2DComponent::addAnimation(std::string name)
{
	auto sprite = g_spriteSystem->getSprite(name);
	if (sprite != nullptr)
	{
		m_spriteMap.insert(std::pair<string, std::shared_ptr<Sprite>>(name, sprite));
	}
}

void Animation2DComponent::update(float deltaTime)
{
	m_timer += deltaTime;
	if (m_timer >= m_animationSpeed) {
		auto sprite = m_spriteMap[m_activeAnimation];
		if (sprite != nullptr) {
			m_frameCounter++;
			if (m_frameCounter >= m_frameCount) {
				m_frameCounter = 0;
			}
		}
		m_timer = 0;
	}
}

void Animation2DComponent::render()
{
	auto sprite = m_spriteMap[m_activeAnimation];
	if (sprite != nullptr) {
		auto transform = gameObject->getComponent<TransformComponent>();
		assert(transform.get() != nullptr && "transform of gameobject with spritecomponent is nullptr");
		if (transform.get() != nullptr) {
			g_drawingSystem->draw(sprite, transform->getGlobalTransform(), m_frameCounter, m_sortingOrder);
		}
	}
}

Animation2DComponent::Animation2DComponent(GameObject * gameObject):
	GameComponent(gameObject)
{
	m_timer = 0;
	m_animationSpeed = 0.2f;
	m_activeAnimation = "";
	m_sortingOrder = 1;
}

int Animation2DComponent::width()
{
	if (m_spriteMap[m_activeAnimation] != nullptr) {
		return m_spriteMap[m_activeAnimation]->width();
	}
	return 0;
}

int Animation2DComponent::height()
{
	if (m_spriteMap[m_activeAnimation] != nullptr) {
		return m_spriteMap[m_activeAnimation]->height();
	}
	return 0;
}

void Animation2DComponent::setSortingOrder(int order)
{
	m_sortingOrder = order;
}

std::shared_ptr<SRE::Mesh> Animation2DComponent::getMesh() {
	auto sprite = m_spriteMap[m_activeAnimation];
	if (sprite != nullptr) {
		return sprite->getMesh();
	}
	return nullptr;
}
