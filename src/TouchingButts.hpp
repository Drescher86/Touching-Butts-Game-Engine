#pragma once

#include "SRE/SimpleRenderEngine.hpp"
#include "SDL.h"
#include "Box2D/Box2D.h"
#include <vector>
#include <memory>
#include "Scene.h"
#include "PhysicsSystem.h"
#include "ParticleSystem/ParticleSystem.h"
#include "DebugSystem.h"
#include "EventSystem.h"
#include "InputSystem.h"
#include "SpriteSystem.h"
#include "DrawingSystem.h"
#include "TouchingButtsGame.h"
#include "SceneSystem.h"
#include "ScriptingSystem.h"

class PhysicsSystem;
class DebugSystem;
class SceneSystem;
class ScriptingSystem;
#ifndef GLOBAL_ENGINE_SYSTEMS
#define GLOBAL_ENGINE_SYSTEMS

extern PhysicsSystem* g_physicsSystem;
extern ParticleSystem* g_particleSystem;
extern DebugSystem* g_debugSystem;
extern EventSystem* g_eventSystem;
extern InputSystem* g_inputSystem;
extern SpriteSystem* g_spriteSystem;
extern DrawingSystem* g_drawingSystem;
extern SceneSystem* g_sceneSystem;
extern ScriptingSystem* g_scriptingSystem;
extern SDL_Window* g_window;
extern Vector2 g_windowSize;
#endif // !GLOBAL_ENGINE_SYSTEMS

/**
Main class runs the game loops and has references to all sub systems.
*/
class TouchingButts : public IEventListener {
public:
	/**
	Initialize function to setup window and initialize sub systems.
	*/
    TouchingButts(int width /** Width of window in pixels*/, int height/** Height of window in pixels*/, TouchingButtsGame * game /** Reference to a implemented version of TouchingButtsGame*/, std::string gameName /** Game name used as title of window*/);
    virtual ~TouchingButts();
	/**
	Starts the game loops. Call only once.
	*/
    void startGameLoop();
	/**
	EventHandler to pause game.
	*/
	void onEvent(BaseEventData eventData) override;
private:
    int m_width;
    int m_height;
	bool m_fullsize;
    int m_quit;
	float m_updateTimer;
	void initializeEngineSystems();
	void postInitializeEngineSystems();
	bool m_isPaused;
	TouchingButtsGame * m_game;
	float m_fixedTimeStep;
	void fixedTimeStep();
	void prePhysicsUpdate();
	void preRenderUpdate();
	void update(float deltaTime);
	void render();
	void postRenderUpdate();
	void postPhysicsUpdate();
	void setupEngineValues();
	void updateEngineValues(float deltaTime);
	SDL_Window* m_window;
	SRE::SimpleRenderEngine* m_sre;
};

