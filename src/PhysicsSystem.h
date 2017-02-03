#pragma once
#include <Box2D/Box2D.h>
#include <map>
#include "Components/ColliderComponent.h"
#include "EngineSystem.h"
#include "SceneSystem.h"

class ColliderComponent;
/**
Physics system responsible for updating the physics world.
*/
class PhysicsSystem : public b2ContactListener, EngineSystem {
public:
	//static PhysicsSystem* instance();
	/**
	Get the Box2D world.
	*/
	b2World* getWorld();
	/**
	Reset the Box2D world.
	*/
	void resetWorld();
	/**
	Eventhandler for contact begin between physics objects.
	*/
	void BeginContact(b2Contact * contact) override;
	/**
	Eventhandler for contact end between physics objects.
	*/
	void EndContact(b2Contact * contact) override;
	/**
	Register new component to the world. Done by collider components internally.
	*/
	void registerComponent(std::shared_ptr<ColliderComponent> component, b2Fixture* fixture);
	/**
	Unregister component from the world. Done by collider components internally.
	*/
	void unregisterComponent(std::shared_ptr<ColliderComponent> component);
	
	PhysicsSystem();
	~PhysicsSystem();
protected:
	virtual bool init() override;
	void update(float deltaTime);
	virtual void shutdown() override;
	void setWorld(b2World* newWorld);
	friend class SceneSystem;
	friend class TouchingButts;
private:
	b2World* m_world;
	std::map<b2Fixture*, std::shared_ptr<ColliderComponent>> m_colliderMap;
	std::vector<std::pair<std::shared_ptr<ColliderComponent>,std::shared_ptr<ColliderComponent>>> m_collidersStay;
};