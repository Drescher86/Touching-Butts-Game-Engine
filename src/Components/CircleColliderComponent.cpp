#include "CircleColliderComponent.h"
#include "TransformComponent.h"
#include "src/GameObject.h"
#include <Box2D/Box2D.h>
#include "src/TouchingButts.hpp"
#include <math.h>


void CircleColliderComponent::onCollisionEnter(std::shared_ptr<ColliderComponent> otherComponent) {
	ColliderComponent::onCollisionEnter(otherComponent);
}
void CircleColliderComponent::onCollisionExit(std::shared_ptr<ColliderComponent> otherComponent) {
	ColliderComponent::onCollisionExit(otherComponent);
}

void CircleColliderComponent::onCollisionStay(std::shared_ptr<ColliderComponent> otherComponent) {
	ColliderComponent::onCollisionStay(otherComponent);
}

void CircleColliderComponent::postInit()
{
	auto transform = gameObject->getComponent<TransformComponent>();
	auto sprite = gameObject->getComponent<SpriteComponent>();
	auto anim = gameObject->getComponent<Animation2DComponent>();
	if (transform != nullptr && (sprite != nullptr || anim != nullptr)) {

		auto position = transform->getPosition();
		b2BodyDef* bodyDef = new b2BodyDef();
		auto scale = transform->getScale();
		float radius = 0.f;
		float offset = 0.f;
		if (sprite != nullptr) {
			radius = sqrt(scale.x * sprite->width() * scale.x * sprite->width()) / 2;
			offset = scale.x * sprite->width() / 2;
		}
		else {
			radius = sqrt(scale.x * anim->width() * scale.x * anim->width()) / 2;
			offset = scale.x * anim->width() / 2;
		}
		bodyDef->position.Set(position.x, position.y);
		if (!m_staticBody) {
			bodyDef->type = b2_dynamicBody;
		}
		else {
			bodyDef->type = b2_staticBody;
		}
		m_body = g_physicsSystem->getWorld()->CreateBody(bodyDef);
		m_body->SetFixedRotation(true);
		
		
		b2CircleShape shape;
		shape.m_radius = radius;
		shape.m_p.Set(offset, offset);
		m_fixture = m_body->CreateFixture(&shape, 1.0f);
		m_fixture->SetRestitution(1);
		ColliderComponent::postInit();
	}
}

CircleColliderComponent::CircleColliderComponent(GameObject * gameObject)
	:ColliderComponent(gameObject) {
	
}
