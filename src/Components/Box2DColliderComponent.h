#pragma once
#include "ColliderComponent.h"
#include <Box2D/Box2D.h>
/**
Box2D collider component.
*/
class Box2DColliderComponent : public ColliderComponent {
public:
	
protected:
	void onCollisionEnter(std::shared_ptr<ColliderComponent> otherComponent) override;
	void onCollisionExit(std::shared_ptr<ColliderComponent> otherComponent) override;
	void onCollisionStay(std::shared_ptr<ColliderComponent> otherComponent) override;
	Box2DColliderComponent(GameObject* gameObject);
	void postInit() override;
private:
	
	friend class GameObject;
};