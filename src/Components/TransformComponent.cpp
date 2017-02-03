#include "TransformComponent.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "src/GameObject.h"

void TransformComponent::move(glm::vec3 moveVector) {
	m_position += moveVector;
	auto collider = gameObject->getComponent<ColliderComponent>();
	if (collider != nullptr) {
		collider->moveObject(m_position);
	}
}

void TransformComponent::move2D(Vector2 moveVector) {
	move(glm::vec3(moveVector.x(), moveVector.y(),0));
}

void TransformComponent::rotate(glm::vec3 rotation) {
	m_rotation += rotation;
}

void TransformComponent::scale(glm::vec3 scale) {
	m_scale *= scale;
}

glm::vec3 TransformComponent::getPosition() {
	return m_position;
}

glm::vec3 TransformComponent::getScale() {
	return m_scale;
}

float TransformComponent::getRotationAroundZAxis() {
	return 0.0f;
}

glm::mat4 TransformComponent::getGlobalTransform() {
	std::shared_ptr<GameObject> parent = gameObject->getParent();
	if (parent != nullptr) {
		auto transform = parent->getComponent<TransformComponent>();
		if (transform != nullptr) {
			return transform->getGlobalTransform() * getLocalTransform();
		}
	}
	return getLocalTransform();
}

void TransformComponent::setPosition(glm::vec3 newPosition) {
	m_position = newPosition;
}

TransformComponent::TransformComponent(GameObject * gameObject)
	:GameComponent(gameObject) {
	m_scale = glm::vec3(1);
}

glm::mat4 TransformComponent::getLocalTransform() {
	return glm::translate(glm::mat4(1.0f), m_position) *
		glm::eulerAngleZ(glm::radians(m_rotation.z)) *
		glm::eulerAngleY(glm::radians(m_rotation.y)) *
		glm::eulerAngleX(glm::radians(m_rotation.x)) *
		glm::scale(m_scale);
}
