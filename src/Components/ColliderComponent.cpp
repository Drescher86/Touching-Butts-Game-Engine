#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "src/GameObject.h"
#include "ScriptableComponent.h"
void ColliderComponent::update() {
	if (m_postInited) {
		if (m_body != nullptr && m_body->GetType() != b2BodyType::b2_staticBody) {
			auto transform = gameObject->getComponent<TransformComponent>();
			if (transform != nullptr && m_body != nullptr) {
				auto pos = m_body->GetPosition();
				//transform->rotate(glm::vec3(0, 0, m_body->GetAngle()));
				transform->setPosition(glm::vec3(pos.x, pos.y, 0));
			}
		}
	}
}

void ColliderComponent::setIfDynamic(bool isDynamic)
{
	m_staticBody = false;
}

void ColliderComponent::setRadius(float radius)
{
	if (m_postInited) {
		if (m_fixture->GetShape() != nullptr)
			m_fixture->GetShape()->m_radius = radius;
	}
}

void ColliderComponent::onCollisionEnter(std::shared_ptr<ColliderComponent> otherComponent){
	auto script = gameObject->getComponent<ScriptableComponent>();
	if (script != nullptr)
		script->onCollisionEnter(otherComponent);
}

void ColliderComponent::onCollisionExit(std::shared_ptr<ColliderComponent> otherComponent) {
	auto script = gameObject->getComponent<ScriptableComponent>();
	if (script != nullptr)
		script->onCollisionExit(otherComponent);
}

void ColliderComponent::onCollisionStay(std::shared_ptr<ColliderComponent> otherComponent) {
	auto script = gameObject->getComponent<ScriptableComponent>();
	if (script != nullptr)
		script->onCollisionStay(otherComponent);
}

void ColliderComponent::moveObject(glm::vec2 moveVector)
{
	if (!g_physicsSystem->getWorld()->IsLocked() && m_postInited) {
		m_body->SetTransform(b2Vec2(moveVector.x, moveVector.y), 0);
		m_body->SetSleepingAllowed(false);
	}
}


ColliderComponent::ColliderComponent(GameObject * gameObject)
	:GameComponent(gameObject), m_postInited(false) {
	m_staticBody = true;
}

void ColliderComponent::postInit()
{
	g_physicsSystem->registerComponent(std::dynamic_pointer_cast<ColliderComponent>(gameObject->getComponentWithId(getId())), m_fixture);
	m_postInited = true;
}

void ColliderComponent::onRemove()
{
	g_physicsSystem->unregisterComponent(std::dynamic_pointer_cast<ColliderComponent>(gameObject->getComponentWithId(getId())));
}

void ColliderComponent::setToTrigger(bool trigger)
{
	m_body->GetFixtureList()[0].SetSensor(trigger);
}

