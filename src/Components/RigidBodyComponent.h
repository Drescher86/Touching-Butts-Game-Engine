#pragma once
#include "GameComponent.h"
#include "src/Vector2.h"
#include "Box2D/Box2D.h"
#include "ColliderComponent.h"
#include <memory>
/**
Rigid body component. Set on a game object to give it a rigid physics body.
*/
class RigidBodyComponent : public ColliderComponent {
public:
	void onCollisionEnter(std::shared_ptr<ColliderComponent> otherComponent) override;
	void onCollisionExit(std::shared_ptr<ColliderComponent> otherComponent) override;
	void onCollisionStay(std::shared_ptr<ColliderComponent> otherComponent) override;
	void applyForce(Vector2 forceVector);
	void applyImpulse(Vector2 impulseVector);
	Vector2 getVelocity();
	void setVelocity(Vector2 vel);
protected:
	RigidBodyComponent(GameObject * gameObject);
	void postInit() override;
	
private:
	friend class GameObject;
};