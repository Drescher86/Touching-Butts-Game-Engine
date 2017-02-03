#pragma once
#include "GameComponent.h"
#include <glm/glm.hpp>
#include <Box2D/Box2D.h>
#include <memory>
/**
Collider base component.
*/
class ColliderComponent : public GameComponent {
public:
	/**
	Move physics object in Box2DWorld.
	*/
	void moveObject(glm::vec2 moveVector/**Move vector.*/);
	/**
	Set if this object should be reacting physcially to collisions or just send events.
	*/
	void setToTrigger(bool trigger/**Whether to trigger or not.*/);
	/**
	Set if the physics object is dynamic or not. Must be called when initialized. Defaults to false.
	*/
	void setIfDynamic(bool isDynamic/**Whether the object is dynamic or not.*/);
	/**
	Set the radius of the collider
	*/
	void setRadius(float radius/**The radius of the circle*/);
protected:
	virtual void onCollisionEnter(std::shared_ptr<ColliderComponent> otherComponent);
	virtual void onCollisionExit(std::shared_ptr<ColliderComponent> otherComponent);
	virtual void onCollisionStay(std::shared_ptr<ColliderComponent> otherComponent);
	virtual void postInit() override;
	virtual void onRemove() override;
	
	void update();

	ColliderComponent(GameObject* gameObject);
	
	
	bool m_staticBody;
	b2Body* m_body;
	b2Fixture* m_fixture;
	bool m_postInited;
	
	friend class PhysicsSystem;
private:

	friend class GameObject;
};
