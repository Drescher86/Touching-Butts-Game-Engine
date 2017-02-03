#include "GameObject.h"
#include "Components/MeshComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/ScriptableComponent.h"
#include "Components/Animation2DComponent.h"
#include "Components/TextComponent.h"
#include "Components/ButtonComponent.h"
#include <time.h>

GameObject::GameObject(std::string name_)
	:m_name(name_), m_gameObjectID(nextGameObjectId++)
{
}

GameObject::~GameObject() {
	auto script = getComponent<ScriptableComponent>();
	if (script != nullptr) {
		script->onDestroy();
	}
}

std::shared_ptr<GameObject> GameObject::clone()
{
	std::shared_ptr<GameObject> clone = std::make_shared<GameObject>(GameObject(m_name));
	std::vector<std::shared_ptr<GameComponent>>::iterator it = m_components.begin();
	for (; it != m_components.end(); it++) {
	}
	return clone;
}

int GameObject::getId()
{
	return m_gameObjectID;
}


std::string GameObject::getName() {
	return m_name;
}


std::shared_ptr<GameComponent> GameObject::getComponentWithId(int id)
{
	auto it = m_components.begin();
	for (; it != m_components.end(); it++) {
		if (it->get()->getId() == id)
			return *it;
	}
	auto it2 = m_componentsToAdd.begin();
	for (; it2 != m_componentsToAdd.end(); it2++) {
		if (it2->get()->getId() == id)
			return *it2;
	}
	return nullptr;
}

bool GameObject::removeComponent(std::shared_ptr<GameComponent> ptr) {
	
	auto it = m_components.begin();
	int i = 0;
	for (; it != m_components.end(); it++) {
		if (*it == ptr)
			break;
		i++;
	}
	if (i >= m_components.size())
		return false;
	
	m_componentsToRemove.push_back(i);
	return true;
}

std::shared_ptr<GameObject> GameObject::getParent() {
	return m_parentObject;
}

void GameObject::setIndestructible(bool value)
{
	m_isIndestructible = value;
}

bool GameObject::isIndestructible()
{
	return m_isIndestructible;
}

void GameObject::postPhysicsUpdate() {
	auto it = m_componentsToRemove.begin();
	for (it; it != m_componentsToRemove.end(); it++)
	{
		m_components.at(*it)->onRemove();				//index
		m_components.erase(m_components.begin() + *it); //iterator
	}
	m_componentsToRemove.clear();
	for (auto & component : m_components)
	{
		component->postPhysicsUpdate();
	}
}

void GameObject::update(float deltaTime){
	for (auto & component : m_components)
	{
		component->update(deltaTime);
	}
}

void GameObject::preRenderUpdate() {
	for (auto & component : m_components)
	{
		component->preRenderUpdate();
	}
}

void GameObject::render() {
	for (auto & component : m_components)
	{
		component->render();
	}
}

void GameObject::postRenderUpdate() {
	for (auto & component : m_components)
	{
		component->postRenderUpdate();
	}
	auto it = m_componentsToAdd.begin();
	for (; it != m_componentsToAdd.end(); it++)
	{
		m_components.push_back(*it);
		it->get()->postInit();
	}
	m_componentsToAdd.clear();
}

void GameObject::prePhysicsUpdate()
{
	for (auto & component : m_components)
	{
		component->prePhysicsUpdate();
	}
}


