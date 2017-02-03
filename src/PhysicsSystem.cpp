#include "PhysicsSystem.h"
#include "Components/ColliderComponent.h"
#include "DebugDraw.h"
b2World * PhysicsSystem::getWorld() {
	initCheck();
	return m_world;
}

void PhysicsSystem::resetWorld() {
	setWorld(new b2World(m_world->GetGravity()));
	DebugDraw* debugDraw = new DebugDraw();
	debugDraw->SetFlags(b2Draw::e_shapeBit);
	m_world->SetDebugDraw(debugDraw);
	m_colliderMap.clear();
	m_collidersStay.clear();
}

void PhysicsSystem::update(float deltaTime) {
	initCheck();
	if (m_world != nullptr) {
		m_world->Step(1/60.0f, 6, 2);
		auto ite = m_colliderMap.begin();
		for (std::map<b2Fixture*, std::shared_ptr<ColliderComponent>>::iterator it = m_colliderMap.begin(); it != m_colliderMap.end(); ++it) {
			it->second->update();
		}
		auto it = m_collidersStay.begin();
		for (; it != m_collidersStay.end(); it++) {
			it->first->onCollisionStay(it->second);
			it->second->onCollisionStay(it->first);
		}
	}
}

void PhysicsSystem::BeginContact(b2Contact * contact) {
	initCheck();
	auto fixture1 = contact->GetFixtureA();
	auto fixture2 = contact->GetFixtureB();
	auto collider1 = m_colliderMap[fixture1];
	auto collider2 = m_colliderMap[fixture2];
	if (collider1 != nullptr && collider2 != nullptr) {
		collider1->onCollisionEnter(collider2);
		collider2->onCollisionEnter(collider1);
	}
	m_collidersStay.push_back(std::pair<std::shared_ptr<ColliderComponent>, std::shared_ptr<ColliderComponent>>(collider1, collider2));
}

void PhysicsSystem::EndContact(b2Contact * contact) {
	initCheck();
	auto fixture1 = contact->GetFixtureA();
	auto fixture2 = contact->GetFixtureB();
	auto collider1 = m_colliderMap[fixture1];
	auto collider2 = m_colliderMap[fixture2];
	if (collider1 != nullptr && collider2 != nullptr) {
		collider1->onCollisionExit(collider2);
		collider2->onCollisionExit(collider1);
	}

	auto it = m_collidersStay.begin();
	for (; it != m_collidersStay.end(); it++) {
		if (it->first == collider1 && it->second == collider2)
			break;
	}
	m_collidersStay.erase(it);
}


void PhysicsSystem::registerComponent(std::shared_ptr<ColliderComponent> component, b2Fixture* fixture) {
	initCheck();
	if (m_colliderMap[fixture] != nullptr) {
		m_colliderMap[fixture] = component;
	}
	else {
		m_colliderMap.insert(std::pair<b2Fixture*, std::shared_ptr<ColliderComponent>>(fixture, component));
		m_colliderMap[fixture] = component;
	}
}

void PhysicsSystem::unregisterComponent(std::shared_ptr<ColliderComponent> component)
{
	for (auto &comp : m_colliderMap){
		if (comp.second == component) {
			m_world->DestroyBody(comp.second->m_body);
			m_colliderMap.erase(comp.first);
			return;
		}
	}
	
}

void PhysicsSystem::setWorld(b2World * newWorld) {
	initCheck();
	m_world = newWorld;
	m_world->SetContactListener(this);
}

PhysicsSystem::PhysicsSystem() {
	//Do nothing!
}

PhysicsSystem::~PhysicsSystem() 
{
	//DO nothing!
}

bool PhysicsSystem::init() {
	EngineSystem::init();
	setWorld(new b2World(b2Vec2(0, -150)));
	initCheck();
	return true;
}

void PhysicsSystem::shutdown()
{
	EngineSystem::shutdown();
}
