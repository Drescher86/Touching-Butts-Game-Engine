#include "Scene.h"
#include "TouchingButts.hpp"
#include <SRE/Mesh.hpp>
#include <SRE/Shader.hpp>
#include "SceneParser.h"
#include "Components/TransformComponent.h"
#include "Components/ScriptableComponent.h"
#include "Components/MeshComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/Animation2DComponent.h"
#include <SRE/SimpleRenderEngine.hpp>

using namespace std;
using namespace SRE;

std::shared_ptr<GameObject> Scene::addGameObject(std::string name) {
	GameObject * go = new GameObject(name);
	auto res = shared_ptr<GameObject>(go);
	m_gameObjectsToAdd.push_back(res);
	return res;
}

bool Scene::removeGameObject(std::shared_ptr<GameObject> ptr) {
	for (auto iter = m_gameObjectsMap.begin(); iter != m_gameObjectsMap.end(); iter++) {
		if (iter->second == ptr) {
			m_objectsToRemove.push_back(iter->first);
			return true;
		}
	}
	// not found
	return false;
}

int Scene::getSize() {
	return (int)m_gameObjectsMap.size();
}

//std::shared_ptr<GameObject> Scene::getGameObject(int index) {
//	if (m_gameObjects.size() > index)
//		return m_gameObjects.at(index);
//	else
//		return nullptr;
//}

void Scene::setName(std::string name)
{
	m_name = name;
}

std::string Scene::getName() {
	return m_name;
}


std::shared_ptr<GameObject> Scene::getGameObjectWithId(int id) {
	auto go = m_gameObjectsMap.find(id);
	if (go != m_gameObjectsMap.end()) {
		return go->second;
	}
	auto it = m_gameObjectsToAdd.begin();
	for (; it != m_gameObjectsToAdd.end(); it++) {
		if (it->get()->getId() == id)
			return *it;
	}
	return nullptr;
}

int Scene::getGameObjectIdFromName(std::string name) {
	auto goIt = m_gameObjectsMap.begin();
	for (; goIt != m_gameObjectsMap.end(); goIt++) {
		if (goIt->second->getName() == name)
			return goIt->first;
	}
	auto it2 = m_gameObjectsToAdd.begin();
	for (; it2 != m_gameObjectsToAdd.end(); it2++) {
		if (it2->get()->getName() == name) {
			return it2->get()->getId();
		}
	}
	return -1;
}

std::shared_ptr<GameComponent> Scene::getComponentWithId(int id)
{
	auto it = m_gameObjectsMap.begin();
	for (; it != m_gameObjectsMap.end(); it++) {
		auto comp = it->second->getComponentWithId(id);
		if (comp != nullptr)
			return comp;
	}

	auto it2 = m_gameObjectsToAdd.begin();
	for (; it2 != m_gameObjectsToAdd.end(); it2++) {
		auto comp = it2->get()->getComponentWithId(id);
		if (comp != nullptr)
			return comp;
	}


	return nullptr;
}


void Scene::prePhysicsUpdate()
{
	for (auto &gameObject : m_gameObjectsMap) {
		gameObject.second->prePhysicsUpdate();
	}
}

void Scene::postPhysicsUpdate() {
	for (auto &gameObject : m_gameObjectsMap) {
		gameObject.second->postPhysicsUpdate();
	}
	for (auto &index : m_objectsToRemove) {
		auto go = m_gameObjectsMap[index];
		auto collider = go->getComponent<ColliderComponent>();
		if (collider != nullptr) {
			g_physicsSystem->unregisterComponent(collider);
		}
		m_gameObjectsMap.erase(index);
	}
	m_objectsToRemove.clear();
}

void Scene::update(float deltaTime) {
	for (auto &gameObject : m_gameObjectsMap) {
		gameObject.second->update(deltaTime);
	}
}


void Scene::render() {
	for (auto &gameObject : m_gameObjectsMap) {
		gameObject.second->render();
	}
}

void Scene::preRenderUpdate()
{
	for (auto &gameObject : m_gameObjectsMap) {
		gameObject.second->preRenderUpdate();
	}
}

void Scene::postRenderUpdate() {
	for (auto &gameObject : m_gameObjectsMap) {
		gameObject.second->postRenderUpdate();
	}

	auto it = m_gameObjectsToAdd.begin();
	for (; it != m_gameObjectsToAdd.end(); it++) {
		m_gameObjectsMap.insert(std::pair<int, std::shared_ptr<GameObject>>(it->get()->getId(), *it));
	}
	m_gameObjectsToAdd.clear();
}



void Scene::load3DFromFile(std::string path) {
	// setup test objec
	shared_ptr<Mesh> sharedMesh(Mesh::createQuad());
	shared_ptr<Mesh> cubeMesh(Mesh::createCube());
	shared_ptr<Mesh> spehereMesh(Mesh::createSphere());
	shared_ptr<Shader> shader(Shader::getUnlit());

	std::vector<GameObjectDescriptor> scene = SceneParser::parse3DFile(path);

	for (auto const& obje : scene)
	{
		auto shptr = addGameObject(obje.name);
		auto transform = shptr->addComponent<TransformComponent>();
		transform->move(obje.position);
		transform->scale(obje.scale);
		transform->rotate(obje.rotationEuler);
		auto render = shptr->addComponent<MeshComponent>();
		render->setShader(shader);
		render->setColor(obje.color);

		if (obje.script != "")
		{
			auto scriptComponent = shptr->addComponent<ScriptableComponent>();
			scriptComponent->loadScript(obje.script, obje.scriptTable);
			scriptComponent->onAwake();
		}

		if (obje.meshName == "plane") {
			render->setMesh(sharedMesh);
		}
		else if (obje.meshName == "cube") {
			render->setMesh(cubeMesh);
		}
		else {
			render->setMesh(spehereMesh);
		}

		if (obje.parentId > -1) {
			shptr->m_parentObject = m_gameObjectsMap[obje.parentId];
		}
	}
}

void Scene::load2DFromFile(std::string path)
{
	
	std::vector<GameObjectDescriptor> scene = SceneParser::parse2DFile(path);

	for (auto const& obje : scene)
	{
		auto shptr = addGameObject(obje.name);
		auto transform = shptr->addComponent<TransformComponent>();
		transform->setPosition(obje.position);
		transform->scale(obje.scale);
		transform->rotate(obje.rotationEuler);
		if (obje.spriteName != "") {
			auto sprite = g_spriteSystem->getSprite(obje.spriteName);
			if (sprite != nullptr) {
				auto spriteComponent = shptr->addComponent<SpriteComponent>();
				spriteComponent->setSprite(sprite);
			}
		}

		if (obje.animationNames.size() > 0) {
			auto animationComponent = shptr->addComponent<Animation2DComponent>();
			if (animationComponent != nullptr) {
				for (auto ani : obje.animationNames) {
					animationComponent->addAnimation(ani);
				}
				animationComponent->playAnimation(obje.animationNames[0]);
			}
		}

		if (obje.script != "")
		{
			auto scriptComponent = shptr->addComponent<ScriptableComponent>();
			scriptComponent->loadScript(obje.script, obje.scriptTable);
		}

		if (obje.parentId > -1) {
			shptr->m_parentObject = m_gameObjectsMap[obje.parentId];
		}
	}
	auto it = m_gameObjectsToAdd.begin();
	for (; it != m_gameObjectsToAdd.end(); it++) {
		m_gameObjectsMap.insert(std::pair<int, std::shared_ptr<GameObject>>(it->get()->getId(), *it));
	}
	m_gameObjectsToAdd.clear();
}

void Scene::addGameObjectAlreadyMade(std::shared_ptr<GameObject> go)
{
	m_gameObjectsToAdd.push_back(go);
}

Scene::Scene() {
}
