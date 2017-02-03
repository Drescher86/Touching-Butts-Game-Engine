#include "RigidBodyComponent.h"
#include "TransformComponent.h"
#include "src/PhysicsSystem.h"
#include "SpriteComponent.h"
#include "src/TouchingButts.hpp"
#include "Animation2DComponent.h"

void RigidBodyComponent::onCollisionEnter(std::shared_ptr<ColliderComponent> otherComponent) {
	ColliderComponent::onCollisionEnter(otherComponent);
}

void RigidBodyComponent::onCollisionExit(std::shared_ptr<ColliderComponent> otherComponent) {
	ColliderComponent::onCollisionExit(otherComponent);
}

void RigidBodyComponent::onCollisionStay(std::shared_ptr<ColliderComponent> otherComponent) {
	ColliderComponent::onCollisionStay(otherComponent);
}

void RigidBodyComponent::applyForce(Vector2 forceVector) {
	if (m_postInited) {
		auto vec = b2Vec2(forceVector.x()*m_body->GetMass(), forceVector.y()*m_body->GetMass());
		m_body->ApplyForce(vec, m_body->GetWorldCenter(), true);
	}
}

void RigidBodyComponent::applyImpulse(Vector2 impulseVector) {
	if (m_postInited) {
		auto vec = b2Vec2(impulseVector.x()*m_body->GetMass(), impulseVector.y()*m_body->GetMass());
		m_body->ApplyLinearImpulse(vec, m_body->GetWorldCenter(), true);
	}
}

Vector2 RigidBodyComponent::getVelocity()
{
	if (m_postInited) {
		return Vector2(m_body->GetLinearVelocity().x, m_body->GetLinearVelocity().y);
	}
	return Vector2(0, 0);
}

void RigidBodyComponent::setVelocity(Vector2 vel)
{
	if (m_postInited){
		m_body->SetLinearVelocity(b2Vec2(vel.x(), vel.y()));
	}
}

RigidBodyComponent::RigidBodyComponent(GameObject * gameObject) : ColliderComponent(gameObject){
	m_postInited = false;
}

void RigidBodyComponent::postInit()
{
	auto transform = gameObject->getComponent<TransformComponent>();
	auto sprite = gameObject->getComponent<SpriteComponent>();
	auto animation = gameObject->getComponent<Animation2DComponent>();
	if (transform != nullptr && (sprite != nullptr || animation != nullptr)) {

		auto scale = transform->getScale();
		auto position = transform->getPosition();
		float angle = transform->getRotationAroundZAxis();
		auto bodyDef = new b2BodyDef();
		bodyDef->type = b2_dynamicBody;
		bodyDef->fixedRotation = true;
		bodyDef->position = b2Vec2(position.x, position.y);

		m_body = g_physicsSystem->getWorld()->CreateBody(bodyDef);
		b2PolygonShape shape;
		int width = 0;
		int height = 0;
		if(animation != nullptr) {
			width = animation->width();
			height = animation->height();
		}
		else {
			width = sprite->width();
			height = sprite->height();
		}
		shape.SetAsBox(scale.x * width / 2, scale.y * height / 2, b2Vec2(scale.x * width / 2, scale.y * height / 2), angle);
		m_fixture = m_body->CreateFixture(&shape, 1.f);

		ColliderComponent::postInit();
	}
	m_postInited = true;
}


