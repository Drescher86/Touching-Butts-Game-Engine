#pragma once

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "GameObject.h"
#include "src/LuaHandlers/LuaSceneHandler.h"
#include "src/Components/GameComponent.h"
#include "src/Components/ScriptableComponent.h"
/**
Scene is responsible for all game objects and runs the update and render functions for all game objects.
*/
class Scene {
public:

	/** 
	Add game object
	*/
	std::shared_ptr<GameObject> addGameObject(std::string name/**Name of game object.*/);
	/** 
	Remove game object
	*/
	bool removeGameObject(std::shared_ptr<GameObject> ptr);
	/** 
	Get number of game objects
	*/
	int getSize();
	/** 
	Get game object by id.
	*/
	std::shared_ptr<GameObject> getGameObjectWithId(int id);
	/**
	get a game objects id from a name - gets the first one if multiple has the same name
	*/
	int getGameObjectIdFromName(std::string name);
	/**
	Get component by id.
	*/
	std::shared_ptr<GameComponent> getComponentWithId(int id);
	/** 
	Returns all components of type C.
	*/
	template<typename C>
	std::vector<std::shared_ptr<C>> getAllComponent();

	/**
	Load a 3D scene from a json file.
	*/
	void load3DFromFile(std::string path/**Path and file name of json file.*/);
	/**
	Load a 2D scene from a json file.
	*/
	void load2DFromFile(std::string path/**Path and file name of json file.*/);
	/**
	Set scene name.
	*/
	void setName(std::string name/**Name of scene.*/);
	/**
	Get scene name.
	*/
	std::string getName();

	/**
	Add an exisiting gameobject to the scene - this is not recommended for normal use!
	*/
	void addGameObjectAlreadyMade(std::shared_ptr<GameObject> go);

	Scene();
protected:
	void update(float deltaTime);
	void render();
	void preRenderUpdate();
	void prePhysicsUpdate();
	void postRenderUpdate();
	void postPhysicsUpdate();
	friend class SceneSystem;
private:
	std::map<int, std::shared_ptr<GameObject>> m_gameObjectsMap;
	std::vector<std::shared_ptr<GameObject>> m_gameObjectsToAdd;
	std::vector<int> m_objectsToRemove;
	std::string m_name;

	friend class LuaSceneHandler;
};



// function templates has to defined in header files
template<typename C>
std::vector<std::shared_ptr<C>> Scene::getAllComponent() {
	std::vector<std::shared_ptr<C>> res;
	for (auto& go : m_gameObjectsMap) {
		std::shared_ptr<C> c = go.second->getComponent<C>();
		if (c.get() != nullptr) {
			res.push_back(c);
		}
	}
	return res;
}