#pragma once
#include "ColliderComponent.h"
/**
Circle collider.
*/
class CircleColliderComponent : public ColliderComponent {
public:
	
protected:
	void onCollisionEnter(std::shared_ptr<ColliderComponent> otherComponent) override;
	void onCollisionExit(std::shared_ptr<ColliderComponent> otherComponent) override;
	void onCollisionStay(std::shared_ptr<ColliderComponent> otherComponent) override;
	void postInit() override;
	CircleColliderComponent(GameObject* gameObject);
private:
	std::shared_ptr<b2CircleShape> m_shape;
	friend class GameObject;
};
