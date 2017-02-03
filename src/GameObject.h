#pragma once
#include "Components/GameComponent.h"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/RigidBodyComponent.h"
#include "Components/Box2DColliderComponent.h"
#include "Components/Animation2DComponent.h"
#include <vector>
#include <memory>
#include <string>

static int nextGameObjectId = 0;
/**
Game object used to represent everything in a scene.
*/
class GameObject {
public:
	~GameObject();
	std::shared_ptr<GameObject> clone();
	/**
	Get ID of game object.
	*/
	int getId();
	/**
	Get name of game object.
	*/
	std::string getName();
	/**
	Add component of C type.
	*/
	template<typename C>
	std::shared_ptr<C> addComponent();
	/**
	Add a component of C type.
	*/
	template<typename C>
	C addComponentNonPointer();
	/**
	Get a component of C type.
	*/
	template<typename C>
	C getComponentNonPointer();
	/**
	Get component by ID.
	*/
	std::shared_ptr<GameComponent> getComponentWithId(int id);
	/**
	Remove Component.
	*/
	bool removeComponent(std::shared_ptr<GameComponent> ptr);
	/**
	Get parent game object.
	*/
	std::shared_ptr<GameObject> getParent();
	/**
	Get component of type C.
	*/
	template<typename C>
	std::shared_ptr<C> getComponent();

	/**
	Set this gameobject to not be removed from the scenegraph when loading new scenes.
	explicit removes will still be available
	*/
	void setIndestructible(bool value);

	/**
	Tells whether or not this game object will be removed from the scene graph when loading new scenes
	*/
	bool isIndestructible();

protected:
	void update(float deltaTime);
	void preRenderUpdate();
	void render();
	void postRenderUpdate();
	void prePhysicsUpdate();
	void postPhysicsUpdate();
	friend class Scene;
private:

	int m_gameObjectID;
	std::vector<std::shared_ptr<GameComponent>> m_components;
	std::vector<std::shared_ptr<GameComponent>> m_componentsToAdd;
	std::vector<int> m_componentsToRemove;

	bool m_isIndestructible = false;

	GameObject(std::string name);
	std::shared_ptr<GameObject> m_parentObject;
	std::string m_name;
	friend class Scene;
};

// function templates has to defined in header files
template<typename C>
std::shared_ptr<C> GameObject::addComponent() {
	C * c = new C(this);
	auto res = std::shared_ptr<C>(c);
	m_componentsToAdd.push_back(res);
	return res;
}

template<typename C>
C GameObject::addComponentNonPointer() {
	auto obj = addComponent<C>();
	return *obj;
}

template<typename C>
std::shared_ptr<C> GameObject::getComponent() {
	for (auto c : m_components) {
		auto castPtr = std::dynamic_pointer_cast<C>(c);
		if (castPtr != nullptr) {
			return castPtr;
		}
	}
	for (auto c : m_componentsToAdd) {
		auto castPtr = std::dynamic_pointer_cast<C>(c);
		if (castPtr != nullptr) {
			return castPtr;
		}
	}
	// not found
	return nullptr;
}

template<typename C>
C GameObject::getComponentNonPointer() {
	for (auto c : m_components) {
		auto castPtr = std::dynamic_pointer_cast<C>(c);
		if (castPtr != nullptr) {
			return *castPtr;
		}
	}
	for (auto c : m_componentsToAdd) {
		auto castPtr = std::dynamic_pointer_cast<C>(c);
		if (castPtr != nullptr) {
			return *castPtr;
		}
	}
}
