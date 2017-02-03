#include "SceneSystem.h"
#include "PhysicsSystem.h"
#include "TouchingButts.hpp"

void SceneSystem::loadScene(std::string sceneName, std::string jsonFile)
{
	Scene* scene = new Scene();
	
	scene->load2DFromFile(jsonFile);
	scene->setName(sceneName);
	auto scen = m_sceneMap.find(sceneName);
	if (scen != m_sceneMap.end()) {
		m_swapScenes.push_back(std::shared_ptr<Scene>(scene));
	}
	else {
		m_sceneMap.insert(std::pair<std::string, std::shared_ptr<Scene>>(sceneName, scene));
	}
}

void SceneSystem::activateScene(std::string sceneName)
{
	auto scene = m_sceneMap.find(sceneName);
	if (scene != m_sceneMap.end()) {
		m_switchToScene = sceneName;
		m_updateScene = true;
	}
}

std::shared_ptr<Scene> SceneSystem::getCurrentScene()
{
	return m_currentScene;
}

void SceneSystem::move2DCamera(Vector2 moveVector)
{
	auto view =glm::translate(m_camera->getViewTransform(), glm::vec3(moveVector.x(),moveVector.y(),0));
	m_camera->setViewTransform(view);
}

void SceneSystem::set2DCameraPosition(Vector2 position)
{
	auto view = glm::translate(glm::vec3(position.x(), position.y(), 0));
	m_camera->setViewTransform(view);
}

void SceneSystem::move3DCamera(Vector3 moveVector)
{
	auto view = glm::translate(m_camera->getViewTransform(), glm::vec3(moveVector.x(), moveVector.y(), moveVector.z()));
	m_camera->setViewTransform(view);
}

void SceneSystem::set3DCameraPosition(Vector3 position)
{
	auto view = glm::translate(glm::vec3(position.x(), position.y(), position.z()));
	m_camera->setViewTransform(view);
}

glm::vec3 SceneSystem::getCameraPosition()
{
	return glm::vec3(m_camera->getViewTransform()[3]);
}

glm::mat4 SceneSystem::getViewTransform()
{
	return m_camera->getViewTransform();
}

void SceneSystem::changeCameraTo3D(int width, int height)
{
	m_camera->setPerspectiveProjection(60, width, height, 1, 1000);
	m_camera->lookAt(glm::vec3(10, 10, 10), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
}

std::shared_ptr<Scene> SceneSystem::getSceneWithName(std::string name)
{
	if(m_sceneMap.find(name) != m_sceneMap.end())
		return m_sceneMap[name];
	return nullptr;
}

bool SceneSystem::init()
{
	m_updateScene = false;

	m_camera = SRE::SimpleRenderEngine::instance->getCamera();
	m_camera->setWindowCoordinates();

	EngineSystem::init();
	initCheck();
	return true;
}

void SceneSystem::postInit()
{
}

void SceneSystem::shutdown()
{
	EngineSystem::shutdown();
	delete m_camera;
	m_camera = nullptr;
}

SceneSystem::SceneSystem()
{
	//do nothing
}

SceneSystem::~SceneSystem()
{
	//do nothing
}

void SceneSystem::performUpdates()
{
	if (m_updateScene) {

		std::vector<std::shared_ptr<GameObject>> indestructibles;
		if (m_currentScene != nullptr) {
			auto scripts = m_currentScene->getAllComponent<ScriptableComponent>();
			auto it = scripts.begin();
			for (; it != scripts.end(); it++) {
				if (it->get()->getGameObject()->isIndestructible()) {
					auto goId = it->get()->getGameObjectId();
					auto go = m_currentScene->getGameObjectWithId(goId);
					indestructibles.push_back(go);
				}
			}
		}

		auto sceneIt = m_swapScenes.begin();
		for (; sceneIt != m_swapScenes.end(); sceneIt++) {
			m_sceneMap.at(sceneIt->get()->getName()).swap(*sceneIt);
		}
		m_swapScenes.clear();
		m_currentScene = m_sceneMap[m_switchToScene];
		m_updateScene = false;
		g_physicsSystem->resetWorld();
		auto comps = m_currentScene->getAllComponent<ScriptableComponent>();
		auto it2 = comps.begin();
		for (it2; it2 != comps.end(); it2++) {
			it2->get()->onAwake();
		}
		set2DCameraPosition(Vector2(0, 0));

		auto it3 = indestructibles.begin();
		for (; it3 != indestructibles.end(); it3++) {
			m_currentScene->addGameObjectAlreadyMade(*it3);
		}
	}
}

void SceneSystem::updateCurrentScene(float deltaTime)
{
	if (m_currentScene != nullptr) {
		m_currentScene->update(deltaTime);
	}
}

void SceneSystem::renderCurrentScene()
{
	if (m_currentScene != nullptr) {
		m_currentScene->render();
	}
}

void SceneSystem::preRenderUpdate()
{
	if (m_currentScene != nullptr) {
		m_currentScene->preRenderUpdate();
	}
}

void SceneSystem::prePhysicsUpdate()
{
	if (m_currentScene != nullptr) {
		m_currentScene->prePhysicsUpdate();
	}
}

void SceneSystem::postRenderUpdate()
{
	if (m_currentScene != nullptr) {
		m_currentScene->postRenderUpdate();
	}
}

void SceneSystem::postPhysicsUpdate()
{
	if (m_currentScene != nullptr) {
		m_currentScene->postPhysicsUpdate();
	}
}


