#pragma once
#include "EngineSystem.h"
#include <string>
#include "Scene.h"
#include <memory>
#include <map>
#include "SRE/SimpleRenderEngine.hpp"
#include "SRE/Camera.hpp"
#include "Vector2.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "glm/gtx/euler_angles.hpp"
#include "Vector3.h"
#include "Components/ScriptableComponent.h"

class ScriptableComponent;

/**
Scene system is responsible for loading scenes and updating and rendering all game objects in current scene.
*/
class SceneSystem : public EngineSystem {
public:
	/**
	Load a scene from a json file.
	*/
	void loadScene(std::string sceneName/** The name of the scene. Used for reference.*/, std::string jsonFile/** Path and file name of the json file including extension.*/);
	/**
	Activate the named scene if it has been loaded.
	*/
	void activateScene(std::string sceneName/**Name of the scene.*/);
	/**
	Get the currently active scene.
	*/
	std::shared_ptr<Scene> getCurrentScene();
	/**
	Move the 2D game camera.
	*/
	void move2DCamera(Vector2 moveVector/** A vector describing how much the camera has to move.*/);
	/**
	Set the position of the 2D game camera.
	*/
	void set2DCameraPosition(Vector2 position/**A vector describing the camera's new position.*/);
	/**
	Move the 3D game camera.
	*/
	void move3DCamera(Vector3 moveVector/** A vector describing how much the camera has to move.*/);
	/**
	Set the position of the 3D game camera.
	*/
	void set3DCameraPosition(Vector3 position/**A vector describing the camera's new position.*/);
	/**
	Get the current camera's position in 3D.
	*/
	glm::vec3 getCameraPosition();
	/**
	Get the current camera's view transform matrix.
	*/
	glm::mat4 getViewTransform();
	/**
	Change camera to 3D. Defaults to 2D.
	*/
	void changeCameraTo3D(int width/** Width of viewport*/, int height/**Height of viewport*/);
	/**
	Get a specific scene.
	*/
	std::shared_ptr<Scene> getSceneWithName(std::string name/**Name of scene.*/);
	
	SceneSystem();
	~SceneSystem();
protected:
	virtual bool init() override;
	virtual void postInit() override;
	virtual void shutdown() override;
	friend class TouchingButts;
private:
	void performUpdates();
	void updateCurrentScene(float deltaTime);
	void renderCurrentScene();
	void preRenderUpdate();
	void prePhysicsUpdate();
	void postRenderUpdate();
	void postPhysicsUpdate();

	std::map<std::string, std::shared_ptr<Scene>> m_sceneMap;
	std::vector<std::shared_ptr<Scene>> m_swapScenes;
	std::shared_ptr<Scene> m_currentScene;

	std::string m_switchToScene;
	bool m_updateScene;

	SRE::Camera * m_camera;

	friend class TouchingButts;
	friend class LuaSceneSystemHandler;
};