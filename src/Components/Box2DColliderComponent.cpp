#include "Box2DColliderComponent.h"
#include "src/GameObject.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "src/TouchingButts.hpp"



void Box2DColliderComponent::onCollisionEnter(std::shared_ptr<ColliderComponent> otherComponent) {
	ColliderComponent::onCollisionEnter(otherComponent);
}

void Box2DColliderComponent::onCollisionExit(std::shared_ptr<ColliderComponent> otherComponent) {
	ColliderComponent::onCollisionExit(otherComponent);
}

void Box2DColliderComponent::onCollisionStay(std::shared_ptr<ColliderComponent> otherComponent) {
	ColliderComponent::onCollisionStay(otherComponent);
}

Box2DColliderComponent::Box2DColliderComponent(GameObject * gameObject): ColliderComponent(gameObject) {
	
}

void Box2DColliderComponent::postInit()
{
	auto transform = gameObject->getComponent<TransformComponent>();
	auto sprite = gameObject->getComponent<SpriteComponent>();
	auto anim = gameObject->getComponent<Animation2DComponent>();
	if (transform != nullptr && (sprite != nullptr || anim != nullptr)) {

		auto scale = transform->getScale();
		auto position = transform->getPosition();
		float angle = transform->getRotationAroundZAxis();
		auto bodyDef = new b2BodyDef();
		bodyDef->position = b2Vec2(position.x, position.y);
		if (!m_staticBody) {
			bodyDef->type = b2_dynamicBody;
		}
		m_body = g_physicsSystem->getWorld()->CreateBody(bodyDef);
		b2PolygonShape shape;

		auto width = 0;
		auto height = 0;
		if (anim != nullptr) {
			width = anim->width();
			height = anim->height();
		}
		else {
			width = sprite->width();
			height = sprite->height();
		}
		
		shape.SetAsBox(scale.x * width / 2, scale.y * height / 2, b2Vec2(scale.x * width / 2, scale.y * height / 2), angle);

		m_fixture = m_body->CreateFixture(&shape, 0.0f);
		ColliderComponent::postInit();
	}
}
